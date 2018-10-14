/*

The general idea
================

Read 8-bit audio samples over the arduino serial input, multiply by the current
volume, and then use them to set the PWM duty cycle on the output pin's timer.
The last part is mostly handled by the TimerOne library.

The samples coming in are 8-bit mono, and our serial read speed maxes out at
115200 bits/second = 14400 bytes/second. I've set the arduino PWM update rate at
8kHz; that is, we send a new sample to the timer 8000 times/second. Arduino runs
at 16MHz, so this gives us a budget of 2000 clock cycles per sample.


Mapping each sample to PWM duty
-------------------------------

A sample value of 128 is silence; 255 and 0 are the extremes. I handle this
inside `sqrt_map`, which is a precomputed table of values for this function:

  sqrt_map[i] == (int) (256.0 * sqrt(abs(i - 128) / 128.0))

I've personally found sqrt to be helpful; it seems to result in a less spiky
signal. Your mileage may vary, though; if you want to try a linear version, you
can replace `sqrt_map[x]` with `(unsigned char) abs(x - 128)` near the bottom of
this file where we emit PWM samples.



Scheduling
----------

Everything on the Arduino side is synchronized to `micros()`. Theoretically this
should mean we're microsecond-exact, but I've not found that to be the case; as
a result, the computer-side driver overfeeds the Arduino sample loop and ends up
slowly accumulating a delay. If anyone knows a fix for this, please file an
issue on the project.

Most of the scheduling logic is managed by maintaining a `next_sample_time`
timestamp; we then wait for `micros()` to catch up, at which point we emit the
value. We don't use `micros()` to set `next_sample_time` while the loop is
going; instead, we add `SAMPLE_MICROS` to the existing `next_sample_time` to
maintain accuracy.


Volume control
--------------

This is a potentiometer hooked up to analog pin 5 (or whatever `VOLUME_PIN` is
set to), and whose ends are hooked to GND and 5V. Basically what you'd expect
for the hardware side.

In software, we do a few things to mitigate the jitter. The most important is
that we sample the volume every iteration -- that is, every incoming audio
sample -- and we maintain a circular buffer of recent values that we average
together to get the volume reading. This works around the very real issue that
the arduino analog read circuitry is subject to electrical jitter, some of which
comes from the sample values being emitted from the board (since the boost
converter and the arduino share a common power supply).

The logic for the sample buffer is in a separate file, `sample-average.h`.

`MAX_EFFECTIVE_VOLUME` is a way to set how intense the maximum volume should be.
If you set it to 1024, then you get complete passthrough: the volume knob is
interpreted in its full range. 768, which works well for me, means that full
volume is 75% of what the circuitry is capable of emitting.


PWM frequency recalculation
---------------------------

Due to switching losses and, I assume, the way nerves work, higher PWM
frequencies result in more current consumption for less sensation. It's a milder
feel, which is good, but if you want intensity you're likely to end up with
electrical burns if you use a high frequency.

To reduce this risk, this code varies the PWM frequency based on the volume. The
frequency range is controlled by two variables, `LOW_HZ` and `HIGH_HZ`, which
indicate the PWM frequency at min and max volume, respectively. `HIGH_HZ` should
always be less than `LOW_HZ`. The default varies from 8000Hz (very soft) to
4000Hz (moderately intense).

If you want more intensity from this system, the first thing you should do is
try decreasing `HIGH_HZ`; 1000Hz and below can be very intense without using
very much power.

There's a small delay and potentially a skip when recalculating the PWM
frequency, so we only do it when the volume changes by more than
`VOLUME_TOLERANCE`, which is 16 by default. This way we don't get bouncy
recalculations if we pick up some jitter.

*/


// Build parameter definitions
#define STEREO        0     // Are we reading two 8-bit samples at a time?
#define LED_UNDERFLOW 1     // Blink LED pin 13 when we have buffer underflows?

#define SAMPLE_HZ     8000  // How often we send new PWM samples to the timer
#define SAMPLE_MICROS (1000000 / SAMPLE_HZ)

#define LOW_HZ  8000        // PWM frequency at volume = 0
#define HIGH_HZ 4000        // PWM frequency at max volume

#define VOLUME_PIN 5        // Analog pin hooked up to volume potentiometer
#define VOLUME_TOLERANCE 16 // When volume changes this much, recalculate PWM
#define VOLUME_SAMPLES 128  // Number of samples in windowed average

#define MAX_EFFECTIVE_VOLUME 768


// Build parameter verification
#if SAMPLE_HZ * (1 + STEREO) > 115200 / 8
#  error sample rate exceeds bandwidth capacity
#endif


// The program
#include <Arduino.h>
#include <TimerOne.h>

#define let auto const

#include "sample-average.h"

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |=  _BV(bit))


sample_average<VOLUME_SAMPLES> vol_samples;

int last_volume   = 0;
int buffer_target = SERIAL_RX_BUFFER_SIZE - 4;

unsigned long next_sample_time;

unsigned char const sqrt_map[256] =
{
  255,254,252,251,250,249,248,247,246,245,244,243,242,241,240,239,238,237,236,235,234,233,232,230,229,228,227,226,225,224,223,221,220,219,218,217,216,215,213,212,211,210,209,207,206,205,204,202,201,200,199,197,196,195,193,192,191,189,188,187,185,184,183,181,180,178,177,176,174,173,171,170,168,167,165,164,162,160,159,157,156,154,152,151,149,147,146,144,142,140,138,137,135,133,131,129,127,125,123,121,119,117,114,112,110,108,105,103,100,98,95,92,90,87,84,81,78,74,71,67,63,59,55,50,45,39,31,22,0,22,31,39,45,50,55,59,63,67,71,74,78,81,84,87,90,92,95,98,100,103,105,108,110,112,114,117,119,121,123,125,127,129,131,133,135,137,138,140,142,144,146,147,149,151,152,154,156,157,159,160,162,164,165,167,168,170,171,173,174,176,177,178,180,181,183,184,185,187,188,189,191,192,193,195,196,197,199,200,201,202,204,205,206,207,209,210,211,212,213,215,216,217,218,219,220,221,223,224,225,226,227,228,229,230,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,254
};


inline int scale_volume(int const v)
{
  return (long) v * MAX_EFFECTIVE_VOLUME >> 10;
}


void setup()
{
  Serial.begin(115200);
  Timer1.initialize(50);

# if LED_UNDERFLOW
  pinMode(13, OUTPUT);
# endif

  sbi(ADCSRA, ADPS2);                   // set fast sample rate for ADC
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);

  pinMode(9,  OUTPUT);
# if STEREO
  pinMode(10, OUTPUT);
# endif
}


void loop()
{
  // Deactivate PWM while we're paused
  Timer1.pwm(9,  0);
# if STEREO
  Timer1.pwm(10, 0);
# endif

  // Wait for samples. When they're available, schedule a sample-emit.
  while (Serial.available() < buffer_target);
  next_sample_time = micros();

  digitalWrite(13, LOW);

  // Play loop: runs as long as we continue to receive data on time
  while (true)
  {
    // Check for buffer overflow and decrease the target fill amount if we see
    // it.
    if (Serial.available() > SERIAL_RX_BUFFER_SIZE - 4)
      buffer_target = max(4, buffer_target - 2);

    // Wait until we're scheduled to go. We need to handle the overflow case: if
    // next_sample_time overflows then everything is fine; this will trip
    // immediately. If micros() overflows first, though, then we're in some
    // trouble. We can figure this out by looking at the high bit of each.
    unsigned long now;
    while (next_sample_time > (now = micros())
        || !(now >> 31 & 1) && (next_sample_time >> 31 & 1))
      // Mitigate buffer overruns while we're waiting. We have a target that is
      // adjusted dynamically as we observe overflow/underflow. Adjustments are
      // rate-limited to specific overflow/underflow events.
      while (Serial.available() > buffer_target)
      {
#       if STEREO
        Serial.read();
#       endif
        Serial.read();
      }

    vol_samples << analogRead(VOLUME_PIN);

    let volume    = vol_samples.mean();
    let amplitude = scale_volume(volume);

    if (abs(volume - last_volume) > VOLUME_TOLERANCE)
    {
      // Recalculate PWM frequency. We want minimum volume to correspond to
      // about 10kHz and maximum volume to be 4kHz -- so a PWM duration range of
      // 100μs to 250μs. I think a linear mapping is fine.
      Timer1.setPeriod((1000000l / LOW_HZ)
                     + ((long) amplitude * (1000000l / HIGH_HZ
                                          - 1000000l / LOW_HZ) >> 10));
      last_volume = volume;
    }

    // Schedule the next output sample
    next_sample_time += SAMPLE_MICROS;

    // Read the left/right serial values, waiting until they come in. Waiting is
    // no problem here; the timeline will be compensated because we maintain
    // absolute sync using next_sample_time.
    //
    // If we wait too long -- in this case running into the next scheduled
    // sample -- then break out of the loop for pause.
    while (Serial.available() < 2)
      if (micros() > next_sample_time)
      {
        // Buffer underflow. We're scheduled to emit a sample but don't have
        // data available; that means we need to increase our target buffer fill
        // amount.
        buffer_target = min(SERIAL_RX_BUFFER_SIZE - 4, buffer_target + 8);
        Timer1.setPwmDuty(9,  0);
        Timer1.setPwmDuty(10, 0);
#       if LED_UNDERFLOW
        digitalWrite(13, HIGH);
#       endif
        return;
      }

    // Read our samples as close as possible to the scheduled time.
    // NB: reversing channels deliberately.
    let right = Serial.read();
    let left_fp_target  = min(1023, (long) amplitude * sqrt_map[right] >> 9);
    Timer1.setPwmDuty(9, left_fp_target);

#   if STEREO
    let left  = Serial.read();
    let right_fp_target = min(1023, (long) amplitude * sqrt_map[left]  >> 9);
    Timer1.setPwmDuty(10, right_fp_target);
#   endif
  }
}

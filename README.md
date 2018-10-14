Audio E-Stim for Ubuntu and Arduino
===================================

The Hardware
------------

Core concepts worth thinking about:

- [Quick guide to electrical theory](doc/electrical-theory.md)
- [How not to die](doc/how-not-to-die.md)
- [How not to hurt yourself](doc/how-not-to-hurt-yourself.md)

Building the L298N board:

- [Shopping list](doc/shopping-list.md)
- [Schematic](doc/schematic.md)
- [Building the board](doc/build.md)


Safety
------

I think this project is pretty safe, but there are a few things I highly
recommend doing:

0. **Read the entire [r/estim
   wiki](https://www.reddit.com/r/estim/wiki/index).** It doesn't take long and
   covers all of the basic safety guidelines.
1. **Never attach outputs above your waist**, even when the unit is off or at
   low volume. The amplifier can produce enough current to cause fibrillation if
   something goes wrong. This is not a medical device, it's a Chinese boost
   converter attached to an Arduino.
2. **Isolate your PC from ground.** If you have a laptop, this means unplugging
   it. Both sides of the output are live relative to the USB ground, which is
   always shorted to your house wiring's earth line. Most of the time you aren't
   likely to be grounded with low impedance (and I regularly use the unit
   plugged in with no problems), but you need to be aware that this is going on.
3. **Test the unit every time:** before connecting anything to yourself, power
   the unit on, turn the volume all the way down, and short the outputs
   together. Then slowly turn the volume up and make sure the power meter shows
   a gradual rise in current. If there's a huge spike from standby to 2A, then
   something is wrong. If there's no current rise at all, then that's also a
   problem.
4. Tap the outputs together briefly before connecting them to you. This isn't a
   safety issue, it just makes sure there's no stored energy in the output
   isolation capacitors.


The Software
------------

- [Technical description in source](src/main.cc)
- [How to build and upload to arduino](doc/platformio.md)


Audio interop
-------------

- [Setting up your audio device](doc/audio-setup.md)
- [Audio send script](./send-audio)

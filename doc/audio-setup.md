Audio setup in Ubuntu
=====================

I assume you have a recent Ubuntu installation (14.04 or later) with working
audio.

Ubuntu may be using either of two audio providers, PulseAudio or ALSA. They
interoperate in some ways. In either case, the first step is to install
`alsa-utils` if you don't already have it:

```
sudo apt install alsa-utils
```

This gives you the `arecord` command, which records audio from a device and
sends it to standard out.

The next step is to set your default recording device to a monitor of your
playback. [This AskUbuntu
answer](https://askubuntu.com/questions/754660/ubuntu-settings-add-recording-device)
covers how you would do that using PulseAudio.

Once you have that set up, you can make sure everything is ready by kicking off
your signal audio, recording into a file, and playing it back:

```
arecord -f cd > file.raw        # hit Ctrl-C after ten seconds or so
```

Now turn off the signal audio and run this:

```
aplay -f cd < file.raw          # this should play signal audio
```

If this all works, then you're ready to send data to the Arduino.


Using stereo audio with mono hardware
-------------------------------------

Stereo EStim signals tend to cancel each other out if you downmix them to mono;
what you want to do instead is just select one channel or the other. I recommend
configuring the audio balance to 100% right or 100% left.

**TODO:** Update this project to accept stereo input

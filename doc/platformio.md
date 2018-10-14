Programming Arduino with PlatformIO
===================================

PlatformIO is a way to manage Arduino projects without using their IDE. I like
it because it lets you have a more conventional software directory layout and is
usable from the command line.

You can install it from [platformio.org](https://platformio.org). Once you've
done that, open a terminal and `cd` into this project directory. You'll then be
able to run two commands:

- `pio run`: compile the project, but don't upload it.
- `pio run -t upload`: compile the project and upload to Arduino.

Neither of these will send any audio to the board, so you won't get any signal
out. For that, you'll need to use the audio interop script.

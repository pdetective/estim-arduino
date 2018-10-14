Building the amplifier
======================

![amp base](https://i.imgur.com/rmKxddk.jpg)

There aren't very many components on the board; most of the space is taken up
by hookup wire. I soldered a couple of square pins onto the boost converter and
plugged it into the side GND/5V rails, then just let it hang off the board
sloppily. You'll notice there's nothing on the `OUT-` connection; the converter
shorts it to `IN-`.


More board detail
-----------------

![board top](https://i.imgur.com/8pp4m7J.jpg)

![board front](https://i.imgur.com/wnuuG6K.jpg)

![next to bare arduino](https://i.imgur.com/s6FfyTm.jpg)

![pins with arduino jacks](https://i.imgur.com/g7qnrVF.jpg?2)

![with output leads](https://i.imgur.com/Eg3Cpz4.jpg)

![with output leads and USB connection](https://i.imgur.com/mL7GP4z.jpg)

You'll probably spend some time looking at the [L298N
datasheet](https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf). In
particular, the pin assignments aren't easy to remember, and it's worth
double-checking them before powering anything up.

When you build the board and power it up for the first time, I recommend leaving
the boost converter off and measuring the current. Then you can tap the boost
converter contacts onto the 5V circuitry and make sure you don't see a massive
short anywhere. With no signal from the computer, I get 0.18A on the USB meter.

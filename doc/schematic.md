Electrical connections
======================

This EStim board is mostly software. Here's how the hardware works:

```
                                 +------------+-----100nF-+
                                 |            |           |
                                 | 30V        |          GND
                                 |            |
                     +--------------+         |
                     | boost module |      +----------------+
                     | 5V -> 30V DC |      |  Vs            |
                     +--------------+      |                |
                       |         |         |                |
                      GND        |         |     L298N      |
                                 |         |                |
        +-------------+          |     +---| EnA       OUT1 |---470nF--- you
        |             |          |     |   |                |
        |          5V |---+------+-----+---| Vss       OUT2 |---470nF--- you
        |             |   |      |     |   |                |
        |          A5 |--VOL     |   100nF |                |
        |             |   |     5kΩ    |   |                |
USB --> | Arduino     |  GND     |    GND  |                |
        |             |          |         |                |
        |             |          +---------| In1            |
        |             |          |         |                |
        |             | +------- | --------| In2 (= D9)     |
        |             | |        |         |                |
        |             | |      |/          | GND   SENSE A  |
        |          D9 |-+-330Ω-| NPN       +--+-------------+
        |             |        |\             |       |
        |             |          |            |       |
        |         GND |----------+------------+-------+
        +-------------+
```

There are a bunch of pins unused on the L298 for the other output. You could
easily implement that on D10 with another transistor/resistor bridge, but you'll
need to run those outputs to a transformer to avoid crossover with the first
channel.

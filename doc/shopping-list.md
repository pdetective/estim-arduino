Shopping list
=============

Test gear (some is required)
----------------------------

You'll need either a multimeter or an oscilloscope depending on your budget.
Multimeters start at about [$5 on
AliExpress](https://www.aliexpress.com/item/New-arrive-Backlight-Digital-LCD-Multimeter-Voltmeter-Ammeter-AC-DC-OHM-Volt-Tester-Test-Current/32652332147.html).
Those are admittedly dodgy, but the dodginess is mostly around high-voltage
protection and this is a low-voltage project. Just put a label on it that says
"don't use this on mains voltage". (Note: I haven't used this specific meter,
but if I were looking for one I'd give it a try.)

Oscilloscopes give you a lot more debugging detail. [Dave Jones
says](https://www.youtube.com/watch?v=rTPhuRQBmLQ) you can get one for about $50
on ebay; in my experience you should plan to spend closer to $100. Used analog
scopes are great: accurate and robust. I'd stay away from the micro
digital-scope kits because they might miss voltage spikes or be unable to handle
the ~60V output.


Power unit supplies
-------------------

Total budget: under $40

- 1x [USB power
  meter](https://www.aliexpress.com/item/USB-Digital-Power-Meter-Tester-battery-capacity-tester-Current-Voltage-Monitor-DC-5A-9V-Voltage-Power/32888681113.html):
  $2. Always use this and keep an eye on the current. Idle should be around 0.02
  amps.

- 2x [Arduino
  Uno](https://www.aliexpress.com/item/high-quality-One-set-UNO-R3-CH340G-MEGA328P-for-Arduino-UNO-R3-USB-CABLE-ATMEGA328P-AU/32810623079.html):
  $3 each. You technically only need one, but I recommend having a spare. It's
  easy to nuke one if you hook it up wrong.

- 1x [Arduino prototyping
  shield](https://www.aliexpress.com/item/MEGA-Proto-Prototype-Shield-V3-0-170pts-Breadboard-for-arduino-mega/32493176287.html),
  the Uno size: $2.

- 1x or 2x [L298N driver
  chip](https://www.aliexpress.com/item/2PCS-L298N-ZIP15-L298-ZIP-new-and-original-IC-In-Stock/32876742145.html):
  $1 each. One of these chips will handle two output channels.

- 1x [boost converter
  module](https://www.aliexpress.com/item/1PCS-XL6009-Boost-Converter-Step-Up-Adjustable-15W-5-32V-to-5-50V-DC-DC-Power/32807346491.html):
  $1.

- [Hookup wire](https://www.amazon.com/dp/B00KAE3NTQ/) if you don't already have
  some. Nothing special, it just needs to be solid core and small enough to fit
  into breadboard holes. About 20AWG is fine.

- [Assorted
  resistors](https://www.aliexpress.com/item/600PCS-Component-Kit-1-1-4W-Resistor-Pack-Used-Colored-Ring-Resistance-10-ohms-1M-ohm/32475181535.html):
  $2.50 for more resistors than you will ever use in your lifetime.

- [Assorted 50V ceramic
  capacitors](https://www.aliexpress.com/item/20PF-105-1UF-50V-18ValuesX10pcs-180pcs-Mono-Monolithic-Capacitors-Monolithic-Ceramic-Capacitor-Assortment-Kit/32304343347.html):
  $1.50, also for more than you'll ever use. The important things are that the
  capacitors are (1) *not* electrolytic, and (2) rated above the boost converter
  voltage. 50V ceramic capacitors will do it.

- [Assorted
  transistors](https://www.aliexpress.com/item/BC337-BC327-2N2222-2N2907-2N3904-2N3906-S8050-S8550-A1015-C1815-Transistor-Assortment-Kit-10value-200PCS-Transistors/32787376478.html):
  $3. You really just need a 2N3904 or similar NPN transistor, but it's good to
  have extras in case you destroy one.


Electrode supplies
------------------

- [Alligator
  clips](https://www.aliexpress.com/item/Brand-New-10pcs-Alligator-Clips-Electrical-DIY-Test-Leads-Alligator-Double-ended-Crocodile-Clips-Roach-Clip/32813105214.html):
  $1.50 for more than you'll need.

- [24AWG bare copper
  wire](https://www.amazon.com/Bare-Copper-Bright-Diameter-Length/dp/B000IJU1ZW):
  $20 for years' worth. The wire gauge is a matter of preference; I use 22AWG,
  which is about right in terms of flexibility. I found 18AWG too stiff.

Electrical connections
======================

There are basically two things going on:

- The Arduino generates a 5V square wave, which goes through a TTL inverter
- The L298N amplifies that signal to about 30V

[Here's a circuit
simulation of the Arduino side.](http://falstad.com/circuit/circuitjs.html?cct=$+1+0.000005+10.20027730826997+50+5+43%0AR+160+256+96+256+0+2+200+2.5+2.5+0+0.5%0Ag+336+320+336+368+0%0Ax+37+211+139+214+4+12+arduino%5Cspin%5Cs9%5Csout%0Aw+160+256+208+256+0%0Aw+208+256+208+128+0%0Aw+208+128+368+128+0%0Ax+383+133+452+136+4+12+to%5CsL298%5CsIN1%0AR+336+160+272+160+0+0+40+5+0+0+0.5%0At+288+256+336+256+0+1+-4.9999999988173505+3.464999999915622e-11+100%0Ar+336+160+336+240+0+5600%0Ar+208+256+288+256+0+330%0Aw+336+272+336+320+0%0Aw+336+240+368+240+0%0Ax+382+245+451+248+4+12+to%5CsL298%5CsIN2%0Ao+12+64+0+4099+5+0.00078125+0+2+12+3%0Ao+5+64+0+4099+5+0.00009765625+1+2+5+3%0A)

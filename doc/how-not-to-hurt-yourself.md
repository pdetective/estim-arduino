How not to hurt yourself
========================

There are a few ways to get hurt with electricity:

1. Run too much current through yourself: you'll get muscular contractions and,
   if you keep it up, electrical burns.
2. Use unbalanced current flow. If you don't balance the current flow, you'll
   accumulate acids and bases on the electrodes and will get chemical burns.
3. Use high-frequency AC at high current. This will cause electrical burns
   without you feeling it.
4. Use electrodes without lubrication, or otherwise poorly connected to the
   skin. This will cause electrical burns, possibly with you feeling it.
5. Use electrically unstable electrodes that will leech materials into your
   body.

[Reddit's EStim
wiki](https://www.reddit.com/r/estim/wiki/index#wiki_material_safety2) covers
(5) in some detail.


Skin characteristics
--------------------

The most important thing to keep in mind is that your skin doesn't behave like a
resistor. You might get 0.1mA at 10V, but 200mA at 80V -- 8x the voltage, 2000x
the current (for example). Here's the **wrong** model, where the skin is treated
like a resistor:

```
  electrode                     inside you

  -----------\               /------------
              \    skin     /
               \___________/
             NOT HOW IT WORKS
               /-----------\
              /             \
  -----------/               \------------
```

Here's a more accurate way to think about it:

```
  electrode                     inside you

  ---------------+-------------------------
        hinge--> o       |
                  \      |
        >>>>       +/////+ <--spring pushing leftwards
        >>>>       \
   flow >>>>        \
        >>>>         \ <--flap
        >>>>          \
                       \

  ---------------+-------------------------
```

Skin initially presents a lot of resistance: the spring holding the flap in
place has some heft to it. Once you get enough pressure to push the flap out of
the way, though, there's very little resistance to additional current.

This is what makes it difficult to design EStim units, and why electricity is
dangerous in general. Any voltage you can feel is likely to be beyond the point
where you skin offers much protection. That isn't a problem if you have current
control; you just need to design the device carefully.


Electrical burns
----------------

More current = more heat. Skin isn't good at conducting heat away from hotspots,
so you'll get blistering if you have a point where heat collects. A few ways to
avoid this:

- Distribute current over a larger area
- Reduce skin resistance (heat output) by improving conductivity
- Decrease the frequency to reduce the amount of time the skin is
  high-resistance
- Use short high-voltage spikes instead of long low-voltage waves

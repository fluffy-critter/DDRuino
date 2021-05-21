# DDRuino

A simple dance pad controller implementation for Arduino devices

(c)2021 j "fluffy" shagam, fluffy@beesbuzz.biz

## About

I was pretty dissatisfied with the code quality of all of the Arduino-based dance pad (DDR/Stepmania/etc.) controller sketches I could find, so I decided to write my own using more-modern C++ with an easier means of configuring things.

This only needs Arduino's default keyboard library, and is intended to let you customize the mapping on a per-pin basis. It requires an Arduino with built-in USB HID support (such as a Leonardo, a LilyPad USB, etc.) and a dance pad that uses contact sensors. I use it with an ATmega 32U4 that I bought off Aliexpress and installed into an [L-Tek](https://www.maty-taneczne.pl/shop/dance-mat-ddr-usb-ex-pro/). See [this tutorial](https://www.instructables.com/Modifying-an-L-tek-Dance-Pad-to-Poll-at-1000hz-on-/) for a pretty good explanation of how to perform the L-Tek mod yourself.

## Usage

Modify the `mapping` array to include all of your active pins and their respective buttons. The mapping provided is just how my pad happens to be wired up; yours will probably vary.

If you have two pads in a doubles set, you'll want to set the pads' arrow buttons to be different keys (for example, `wasd` for the left pad and `ijkl` for the right pad).

If you're not sure how your pins are connected, you can uncomment the `#define DEBUG` line and then run the sketch with the serial monitor enabled, and it'll give you a continuous display of which pins are currently active. Just remember to disable debug mode (i.e. comment the `#define` back out) before you start using the pad for actual gameplay; leaving it enabled will vastly lower your input sampling rate.

Debouncing is on a per-switch basis so it shouldn't be necessary to make it shorter than 20ms (which allows a peak of 25 steps per second on a single switch) but it's probably safe to reduce it further. The minimum safe debounce time will depend a lot on your individual pad. This particular (simple) debounce implementation will never add latency to an initial step.

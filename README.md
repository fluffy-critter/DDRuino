# DDRuino

A simple DDR controller implementation for Arduino devices

(c)2021 j "fluffy" shagam, fluffy@beesbuzz.biz

## About

I was pretty dissatisfied with the code quality of all of the Arduino-based DDR controller sketches I could find, so I decided to write my own using more-modern C++ with an easier means of configuring things.

This only needs Arduino's default keyboard library, and is intended to let you customize the mapping on a per-pin basis.

## Usage

Modify the `mapping` array to include all of your active pins and their respective buttons. The mapping provided is just how my pad happens to be wired up; yours will probably vary.

If you have two pads in a doubles set, you'll want to set the pads' arrow buttons to be different keys (for example, `wasd` for the left pad and `ijkl` for the right pad).

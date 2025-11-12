# handwired/quacknumpad

![quacknumpad](imgur.com image replace me!)

A custom handwired numpad with function keys, using shift registers for column scanning.

* Keyboard Maintainer: [Leonidas Stratigakis](https://github.com/leoquack)
* Hardware Supported: RP2040, HC595 shift registers
* Hardware Availability: Handwired

Make example for this keyboard (after setting up your build environment):

    make handwired/quacknumpad:default

Flashing example for this keyboard:

    make handwired/quacknumpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
* **Physical reset button**: Double tap the reset button on the RP2040
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

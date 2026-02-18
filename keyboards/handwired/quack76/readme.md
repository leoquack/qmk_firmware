# handwired/quack76

![quack76](https://i.imgur.com/placeholder.png)

A 76-key full-size keyboard with rotary encoder, using direct GPIO multiplexing on RP2040.

* Keyboard Maintainer: [Leonidas Stratigakis](https://github.com/Leonidas-Stratigakis)
* Hardware Supported: RP2040-based controllers
* Hardware Availability: Custom handwired/PCB design

## Features

- **76 keys** in standard full-size layout
- **Rotary encoder** for volume/media control
- **Direct GPIO multiplexing** - No shift registers needed!
- **6×14 matrix** using only 20 GPIO pins
- **RP2040** microcontroller (30 GPIO available)

## Layout

```
┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┐
│Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │Enc│
└───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┘
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │   Shift  │
├────┬───┴┬──┴─┬─┴───┴──┬┴───┴──┬┴───┴──┬┴──┬┴──┬┴──┬───────┤
│Ctrl│Win │Alt │ Space  │  FN   │  Alt  │Win│Men│Ctl│
└────┴────┴────┴────────┴───────┴───────┴───┴───┴───┴───────┘
```

## Hardware Design

### Standard QMK Matrix - No Custom Code Needed!

This keyboard uses **QMK's built-in matrix scanning** configured entirely through `keyboard.json`. No custom matrix implementation required!

**When you DON'T need custom matrix:**
- ✅ Standard row/column GPIO pins (that's us!)
- ✅ Direct RP2040 GPIO access
- ✅ Standard diode direction (COL2ROW)

**When you DO need custom matrix:**
- ❌ Shift registers (74HC595, etc.)
- ❌ I2C/SPI port expanders
- ❌ Non-standard hardware configurations

Our setup uses **20 GPIO pins** (6 rows + 14 columns) out of RP2040's **30 available**. QMK's built-in scanning handles this perfectly—it's well-tested, optimized, and requires zero custom code.

### Why No Shift Registers?

Since RP2040 has 30 GPIO pins and we only need 20 (6 rows + 14 columns), **direct GPIO is the obvious choice**:

- ✅ **Simpler** - Uses QMK's built-in matrix scanning
- ✅ **Faster** - No SPI communication overhead
- ✅ **Cheaper** - Eliminates shift register ICs (~$0.06/board savings)
- ✅ **Easier to route** - Fewer components on PCB
- ✅ **More reliable** - Fewer points of failure
- ✅ **Better tested** - QMK's standard matrix code is battle-tested

**Shift registers only make sense when:**
- You need >30 GPIO pins, OR
- Your MCU is severely pin-constrained

For a 76-key keyboard on RP2040? Direct GPIO wins every time.

### GPIO Pin Assignment

**Rows (6 pins):** GP0-GP5
**Columns (14 pins):** GP6-GP19
**Rotary Encoder:** GP20 (A), GP21 (B)
**Reserved for future:** GP22-GP29 (LEDs, debugging, expansion)

This consecutive pin assignment simplifies PCB routing significantly.

### BOM Cost Comparison

| Component | Shift Register Design | Direct GPIO Design |
|-----------|----------------------|-------------------|
| Microcontroller | RP2040 ($3.50) | RP2040 ($3.50) |
| Shift Registers | 2× 74HC595 ($0.06) | None |
| Extra passives | ~$0.05 | None |
| PCB complexity | Higher | Lower |
| **Total savings** | - | **~$0.11 + simpler routing** |

At scale (100+ units), this saves $11+ and reduces assembly time/complexity.

## Building

```bash
make handwired/quack76:default
```

## Flashing

```bash
make handwired/quack76:default:flash
```

Put the keyboard into bootloader mode by double-tapping the reset button or holding the top-left key (Esc) while plugging in.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down Esc (top left key) and plug in the keyboard
* **Physical reset button**: Double-tap the reset button on the RP2040
* **Keycode in layout**: Press `QK_BOOT` (Fn+Esc in default keymap)

## Customization

The rotary encoder is mapped to volume up/down by default. Edit the encoder map in your keymap to change its function.

## License

GPL-2.0-or-later

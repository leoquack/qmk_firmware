# handwired/quackmux

GPIO-multiplexed keyboard using RP2040.

## Overview

This is an improved version of quackshift that eliminates the SPI shift register overhead by using direct GPIO column multiplexing. 

## Hardware Design

**Matrix Configuration:**
- 4 rows × 8 columns
- Column activation: Direct GPIO pins (NO shift registers)
- Row detection: Direct GPIO with pull-down resistors

**GPIO Pin Usage (RP2040):**
- **Columns:** GP0-GP7, GP10-GP11 (8 pins total) - Connected to N-channel transistor bases/gates
- **Rows:** GP6-GP9 (4 pins) - Direct GPIO reads

## Advantages Over quackshift

| Aspect | quackshift (SPI) | quackmux (GPIO) |
|--------|---|---|
| Hardware Cost | 2× HC595 + caps/resistors | 8× transistors only |
| JLCPCB Assembly | More expensive | Cheaper |
| Scan Overhead | ~15-20% SPI time | ~2-5% GPIO time |
| Code Complexity | SPI driver dependency | Simple GPIO writes |
| PCB Routing | SPI bus required | Simpler |

## KiCad Schematic Notes

See `KICAD_DESIGN_NOTES.md` for detailed PCB design guidance.

## Building

```bash
make handwired/quackmux:default
```

## Flashing

```bash
make handwired/quackmux:default:flash
```

## License

GPL-2.0-or-later

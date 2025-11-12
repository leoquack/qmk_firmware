# handwired/quacknumpad

![quacknumpad](imgur.com image replace me!)

A custom handwired numpad with function keys.

* Keyboard Maintainer: [Leonidas Stratigakis](https://github.com/leoquack)
* Hardware Supported: RP2040
* Hardware Availability: Handwired

## Wiring Diagram

### Matrix Layout (6 rows × 4 columns)

```
     COL0   COL1   COL2   COL3
     GP0    GP1    GP2    GP3
      |      |      |      |
ROW0──┼──────┼──────┼──────┼──  GP6
 F1   F2     F3     F4
      |      |      |      |
ROW1──┼──────┼──────┼──────┼──  GP7
 Num  /      *      -
      |      |      |      |
ROW2──┼──────┼──────┼──────┼──  GP8
 7    8      9      + (2u)
      |      |      |      |
ROW3──┼──────┼──────┼──────┼──  GP9
 4    5      6      
      |      |      |      |
ROW4──┼──────┼──────┼──────┼──  GP10
 1    2      3      Ent(2u)
      |      |      |      |
ROW5──┼──────┼──────┼──────┼──  GP11
 0 (2u)      .      
```

### Pin Assignments
- **Rows:** GP6, GP7, GP8, GP9, GP10, GP11
- **Columns:** GP0, GP1, GP2, GP3
- **LED (Num Lock):** GP14

### Diode Direction: COL2ROW
Each switch needs a diode with:
- **Cathode (black band)** → Column wire
- **Anode** → Row wire

### Physical Wiring Steps

1. **Row Wiring:**
   - Connect all switches in each horizontal row together
   - Wire to corresponding RP2040 GPIO (GP6-GP11)
   
2. **Column Wiring:**
   - Connect switches in each vertical column via diodes
   - Diode cathode (marked end) goes to column wire
   - Wire each column to RP2040 GPIO (GP0-GP3)

3. **Special Keys:**
   - **+ key (ROW2, COL3):** Physical key is 2u tall, but electrically just one switch
   - **Enter key (ROW4, COL3):** Physical key is 2u tall, but electrically just one switch  
   - **0 key (ROW5, COL0):** Physical key is 2u wide, but electrically just one switch

4. **LED (Optional):**
   - Num Lock LED: Connect LED anode to GP14 through 220Ω resistor, cathode to GND

### Matrix Positions
```
┌─────┬─────┬─────┬─────┐
│ 0,0 │ 0,1 │ 0,2 │ 0,3 │  F1    F2    F3    F4
├─────┼─────┼─────┼─────┤
│ 1,0 │ 1,1 │ 1,2 │ 1,3 │  Num   /     *     -
├─────┼─────┼─────┼─────┤
│ 2,0 │ 2,1 │ 2,2 │ 2,3 │  7     8     9     +
├─────┼─────┼─────┤     │                    │
│ 3,0 │ 3,1 │ 3,2 │     │  4     5     6     │
├─────┼─────┼─────┼─────┤
│ 4,0 │ 4,1 │ 4,2 │ 4,3 │  1     2     3     Ent
├─────┴─────┼─────┤     │                    │
│   5,0     │ 5,2 │     │  0            .    │
└───────────┴─────┴─────┘
```

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

# handwired/quacknumpad

![quacknumpad](imgur.com image replace me!)

A custom handwired numpad with function keys.

* Keyboard Maintainer: [Leonidas Stratigakis](https://github.com/leoquack)
* Hardware Supported: RP2040
* Hardware Availability: Handwired

## Default keymap

The active layer is selected by a maintained two-pin SPST switch such as the
KCD11-101. An open switch selects the normal numpad layer; closing the switch
selects the drawing layer. The physical position therefore always shows which
mode is active, without needing an indicator LED.

### Drawing layer

| Physical key | Output | Suggested action |
|---|---|---|
| F1 | Alt + Space + left click | Zoom out |
| F2 | Ctrl + Space + left click | Zoom in |
| F3 | `[` | Decrease brush size |
| F4 | `]` | Increase brush size |
| Num | F13 | Color Picker popup |
| / | E | Eraser |
| * | Ctrl + Shift + B | Pencil |
| - | B | Brush |
| 7 | Ctrl + Z | Undo |
| 8 | Ctrl + Shift + Z | Redo |
| 9 | F14 | Flip canvas horizontally |
| + | I | Eyedropper |
| 4 | R | Rotate View tool |
| 5 | Ctrl + S | Save |
| 6 | F15 | Reset canvas rotation |
| 1 | Ctrl + T | Free Transform |
| 2 | Ctrl + D | Deselect |
| 3 | L | Lasso |
| Enter | Ctrl + 0 | Fit to Screen |
| 0 | Space | Hand/pan modifier |
| . | Tab | Toggle interface/palettes |

The zoom and pan keys remain held for as long as their physical keys are held,
so they can be used while dragging rather than as one-shot macros.

### Application setup notes

F13–F15 are useful macro-pad outputs because they normally have no existing
application action. QMK supports them as ordinary `KC_F13`, `KC_F14`, and
`KC_F15` keycodes, while each drawing application can map them to its own
equivalent command:

- **F13 — Color Picker popup.** In Clip Studio Paint, open **File → Shortcut
  Settings → Pop-up palettes → Color Wheel** and assign F13. This avoids
  hard-coding Photoshop's HUD Color Picker mouse gesture in the shared layer.
- **F14 — Flip Canvas Horizontal.** Assign F14 to the equivalent command in
  both Photoshop and Clip Studio Paint. The physical key remains consistent
  even though the applications' native shortcuts differ.
- **F15 — Reset Canvas Rotation.** Assign F15 directly in each application.
  This is safer than Escape, whose meaning depends on context and can cancel a
  transformation, selection, dialog, or text edit.

The remaining choices favor shortcuts that are common or easy to standardize:
R selects Rotate View, L selects Lasso, Ctrl+0 fits the canvas to the screen,
and Tab toggles panels/palettes in both Photoshop and Clip Studio Paint. If an
application uses Ctrl+0 for something else, reassign its Fit to Screen command
to Ctrl+0 or change the firmware output to an unused function key such as F16.

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
- **Layer switch:** GP14

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

4. **Layer Switch:**
   - Connect either KCD11-101 pin to **GP14**
   - Connect the other switch pin to **GND**
   - No resistor is needed; the firmware enables the RP2040's internal pull-up
   - Switch open selects numpad mode; switch closed selects drawing mode
   - The firmware debounces the switch and reads its position at startup, so
     the correct layer is selected immediately after plugging in the keyboard

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

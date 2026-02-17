# KiCad Design Notes: RP2040 Onboarding for JLCPCB

## Don't Copy Pico Blindly - Use a Reference Instead

You're right to hesitate. The Pico has many optional features you don't need. Instead:

### Good Open Source References:
1. **Adafruit QT Py RP2040** - Minimal, clean design (recommended)
   - GitHub: adafruit/Adafruit_PCB
   - Very lean: just the essentials
   
2. **RP2040 Reference Design** - Official from Raspberry Pi
   - GitHub: raspberrypi/hardware
   - Download the `.kicad_sch` files directly
   
3. **Open Source Keyboards using RP2040**
   - Sofle (search GitHub)
   - Nice!Nano RP2040 (nanos/nice3)
   - These often have production PCBs optimized for JLCPCB

### Why Pico is Overkill:
- Has on-board USB connector (you might want yours different)
- Has status LEDs and power LEDs (you don't need)
- Has external flash circuit (unnecessary complexity)
- Has oscillator for WiFi (irrelevant here)
- Unnecessary ground planes for wireless

---

## Minimal RP2040 Schematic for Your Keyboard

You need ONLY these components:

### Essential (5 components):

```
1. RP2040 Microcontroller (BGA100 package)
   - From JLCPCB parts: C2040 or search "RP2040"
   - Cost: ~$3-5

2. 12 MHz Crystal Oscillator
   - Package: 4-pin SMD (5x3.2mm typical)
   - Value: 12MHz
   - From JLCPCB: Many options ~$0.05

3. Two 20pF Capacitors (crystal load capacitors)
   - Package: 0603
   - Part: C0603X5R0J206M030BC or similar
   - Cost: ~$0.01 each

4. TEN 100nF Decoupling Capacitors (VERY IMPORTANT)
   - Package: 0603
   - One per power pin + 2 extra
   - Cost: ~$0.01 each

5. One 1μF Capacitor (power supply bypass)
   - Package: 0603
   - Cost: ~$0.01
```

**That's it. Total component cost: ~$5 + parts**

### Optional but Recommended (2 components):

```
6. Reset Button + Pull-Up
   - 10k resistor (0603) + tactile button
   - Lets you manually force bootloader mode
   - Cost: ~$0.02

7. USB Connector + ESD Diodes
   - USB-C connector (depends on your choice)
   - Two ESD protection diodes
   - Cost: ~$0.20
```

---

## Minimal Schematic Layout

```
                    ┌─────────────────────┐
    12MHz OSC ──┤X1                       │
               │                         │
    20pF Cap──┤LS1  RP2040              │
    20pF Cap──┤LS2                      │
               │                         │
    100nF x10──┤ VCCIO pins (all)       │
    1μF ────┤ VCC (Power)            │
               │                         │
    GPIO ──────┤ GPIO 0-27              ├───→ To Matrix Hardware
    Reset ─────┤ RESET (with 10k pull-up)  (transistors, buttons, etc)
    USB ────────┤ DP/DM pins           │
               └─────────────────────┘
```

---

## JLCPCB Assembly Checklist

When ordering from JLCPCB:

- ✅ Order as "SMD Assembly" (they'll place components)
- ✅ Ensure all parts are in JLCPCB stock (search part numbers!)
- ✅ RP2040 should have status "stock" (it's common now)
- ✅ Provide `.kicad_sch` and `.kicad_pcb` files
- ✅ Provide BoM (Bill of Materials) in their CSV format
- ✅ Provide Pick & Place file (.csv)

### JLCPCB Part Search Tips:
- Search for "RP2040" alone (they'll suggest compatible parts)
- For crystals: search "12MHz OSC SMD"
- They list stock quantity - ensure enough for your order
- Typical lead time: 2-3 weeks

---

## PCB Layout Considerations

### Power Distribution:
- **Star topology** for ground (critical!)
- Thick traces from USB connector to RP2040 power pins
- Decouple each VCCIO pin individually (no sharing traces)

### Signal Integrity:
- USB lines: 90 ohm differential impedance (mention in KiCad design rules)
- Crystal traces: **SHORT** (should be <5mm total)
- Crystal to RP2040 ground plane: Multiple vias nearby

### Thermal:
- RP2040 has ~13 GND pads (BGA)
- Use plenty of vias for thermal transfer
- Add ground plane on Layer 2 under RP2040

---

## Next Steps

1. **Download Adafruit QT Py RP2040 schematic** from their GitHub
2. **Extract the RP2040 schematic portion** (ignore USB power management if different)
3. **Adapt to your matrix hardware**:
   - Remove Adafruit extra features
   - Keep the power/crystal/reset core circuit
   - Add connections to your column/row transistors

4. **Cross-reference with:**
   - RP2040 Datasheet: Official pin functions
   - Raspberry Pi Hardware Design Guide: Best practices

This takes ~2-3 hours if you're new to KiCad, but the result is production-grade and JLCPCB will assemble it smoothly.

---

## Cost Estimate (Per Board)

| Component | Unit Cost | Qty | Total |
|-----------|-----------|-----|-------|
| RP2040 | $3.50 | 1 | $3.50 |
| 12MHz Crystal | $0.05 | 1 | $0.05 |
| 20pF Cap | $0.01 | 2 | $0.02 |
| 100nF Cap | $0.01 | 12 | $0.12 |
| 1μF Cap | $0.01 | 1 | $0.01 |
| 8× Column Transistors | $0.05 | 8 | $0.40 |
| Other passives | ~$0.05 | - | $0.05 |
| PCB Manufacturing | - | - | ~$0.50-1.00 |
| JLCPCB Assembly | - | - | ~$2-4 (volume dependent) |
| **TOTAL PER BOARD** | - | - | **~$6-10** |

(Not including switches, stabilizers, case, or USB cable)

---

**Key Takeaway:** Onboarding RP2040 is straightforward if you use an existing reference design as your template. JLCPCB handles it routinely, and the cost savings vs. a Pico module pay for itself at scale.

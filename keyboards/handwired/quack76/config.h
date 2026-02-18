// Copyright 2024 Leonidas Stratigakis (@Leonidas Stratigakis)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Quack76 - 76-key Full-Size Keyboard with Rotary Encoder
 *
 * Standard QMK Matrix Configuration
 * Matrix: 6 rows × 14 columns = 84 possible positions (76 keys used)
 * Total GPIO used: 20 pins (6 rows + 14 columns)
 *
 * Pin Assignment (defined in keyboard.json):
 * - Rows: GP0-GP5 (6 consecutive pins)
 * - Columns: GP6-GP19 (14 consecutive pins)
 * - Rotary Encoder: GP20 (A), GP21 (B)
 *
 * This uses QMK's built-in matrix scanning - no custom code needed!
 */

/* Matrix Configuration */
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

/* Note: Matrix pins and encoder pins are defined in keyboard.json */

/* Bootloader Configuration */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* Optional: Debug Configuration */
// Uncomment these for debugging via serial console
// #define CONSOLE_ENABLE
// #define DEBUG_MATRIX_SCAN_RATE

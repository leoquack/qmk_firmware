// Copyright 2024 Leonidas Stratigakis (@Leonidas Stratigakis)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * GPIO Multiplexed Matrix Configuration
 *
 * This version uses direct GPIO pins for column activation instead of SPI + shift registers.
 * Simpler hardware, lower cost, faster scanning.
 *
 * RP2040 GPIO Pin Assignment:
 * Columns: GP0-GP7 (8 pins) - Connect to transistor bases/gates for column drivers
 * Rows: GP6-GP9 (4 pins) - Direct GPIO reads for row detection
 *
 * Note: This is a template. Adjust pin assignments based on your actual PCB layout.
 */

/* Feature Configuration */
#define MATRIX_ROWS 4
#define MATRIX_COLS 8

/* GPIO Pin Definitions */
// Column selection pins (directly drive transistor gates/bases)
#define COL_PINS { GP0, GP1, GP2, GP3, GP4, GP5, GP10, GP11 }

// Row detection pins (direct GPIO reads with pull-down)
#define ROW_PINS { GP6, GP7, GP8, GP9 }

/* Enable Features */
#define ENABLE_DEBOUNCE 5

/* Bootloader Configuration */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* Optional: Debug output */
// #define CONSOLE_ENABLE
// #define DEBUG_ENABLE

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
// Using GP12-GP19 for better PCB routing and to avoid USB/Debug pin conflicts
#define COL_PINS { GP12, GP13, GP14, GP15, GP16, GP17, GP18, GP19 }

// Row detection pins (direct GPIO reads with pull-down)
// Using GP20-GP21, GP22, GP26 (avoiding GP23-GP25 used for SPI flash on some boards)
#define ROW_PINS { GP20, GP21, GP22, GP26 }

/* Bootloader Configuration */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* Optional: Debug output */
// #define CONSOLE_ENABLE
// #define DEBUG_ENABLE

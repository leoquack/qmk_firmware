// Copyright 2024 Leonidas Stratigakis (@Leonidas Stratigakis)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// Define your HC595 pin mappings
#define SPI_DRIVER SPID0
#define SPI_MOSI_PIN GP3
// #define SPI_MISO_PIN GP0
#define SPI_SCK_PIN GP2
#define SPI_COL_MATRIX_CS_PIN GP1
#define SPI_DIVISOR 16
#define SPI_lsbFirst true

// Define your keyboard matrix
#define MATRIX_ROWS 6
#define MATRIX_COLS 4

#define ROWS { GP6, GP7, GP8, GP9, GP10, GP11 }
// Hexadecimal:  0    1    2    3
// Binary:    0001 0010 0100 1000
// 0x0001, 0x0002, 0x0004, 0x0008
// 1QA     1QB     1QC     1QD
#define COLS { 0x0001, 0x0002, 0x0004, 0x0008 }

/* Double tap reset button to enter bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define LED_NUM_LOCK_PIN GP14

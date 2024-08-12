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
#define MATRIX_ROWS 4
#define MATRIX_COLS 8

#define ROWS { GP6, GP7, GP8, GP9 }
// Hexadecimal:  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
// Binary:    0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111
//0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000
// 1QA     1QB     1QC     1QD     1QE     1QF     1QG     1QH     2QA     2QB     2QC     2QD     2QE     2QF     2QG     2QH
#define COLS { 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0400, 0x0800, 0x1000 }


/* Double tap reset button to enter bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

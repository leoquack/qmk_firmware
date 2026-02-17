// Copyright 2024 Leonidas Stratigakis (@Leonidas Stratigakis)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "wait.h"

#if defined(CONSOLE_ENABLE)
#    include "print.h"
#endif

/*
 * Custom Matrix Implementation with GPIO Column Multiplexing
 *
 * This keyboard uses direct GPIO pins for column selection (no shift registers).
 * This simplifies the hardware, reduces BOM cost, and eliminates SPI overhead.
 *
 * Matrix scanning process:
 * 1. Set one column GPIO pin HIGH, all others LOW
 * 2. Wait briefly for outputs to settle
 * 3. Read all row pins to detect key presses in that column
 * 4. Repeat for all columns
 * 5. Compare with previous scan to detect changes
 */

// Column GPIO pins (from config.h COL_PINS)
static const pin_t col_pins[MATRIX_COLS] = COL_PINS;

// Row GPIO pins (from config.h ROW_PINS)
static const pin_t row_pins[MATRIX_ROWS] = ROW_PINS;

// Size of matrix in bytes for memcpy/memcmp operations
static const size_t msize = MATRIX_ROWS * sizeof(matrix_row_t);

// Previous matrix state for change detection
static matrix_row_t prev_matrix[MATRIX_ROWS];

/**
 * Read all row pins and pack their states into a single byte
 *
 * @return uint8_t - Bitmask where bit N represents row N state (1 = pressed)
 */
static inline uint8_t read_rows(void) {
    uint8_t row_state = readPin(row_pins[0]);

    for (uint8_t row = 1; row < MATRIX_ROWS; row++) {
        row_state |= (readPin(row_pins[row]) << row);
    }

    return row_state;
}

/**
 * Select a column by setting its GPIO pin HIGH and all others LOW
 *
 * This directly activates the column driver transistor without any shift register.
 * The hardware switches the column on, we wait briefly for stabilization, then
 * read the rows.
 *
 * @param col - Column index to select (0 to MATRIX_COLS-1)
 */
static inline void select_col(uint8_t col) {
    // Set all column pins low first
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        writePin(col_pins[i], 0);
    }

    // Then set only the desired column high
    writePin(col_pins[col], 1);

    // Wait for column to stabilize before reading rows
    matrix_io_delay();
}

/**
 * Initialize the matrix scanning hardware
 *
 * Sets up all column pins as outputs and row pins as inputs with pull-down
 * resistors for stable key detection.
 */
void matrix_init_custom(void) {
#if defined(CONSOLE_ENABLE)
    // Delay for USB serial connection when debugging
    wait_ms(1000);
#endif

    // Configure all column pins as outputs (initially low)
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        setPinOutput(col_pins[col]);
        writePin(col_pins[col], 0);
    }
    matrix_io_delay();

    // Configure all row pins as inputs with pull-down resistors
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        setPinInputLow(row_pins[row]);
    }
    matrix_io_delay();
}

/**
 * Scan the entire matrix and detect changes
 *
 * Iterates through all columns, activating each via GPIO and reading the
 * corresponding row states. Compares the result with the previous scan to
 * determine if any keys changed state.
 *
 * @param current_matrix - Array to store current matrix state
 * @return bool - true if any key state changed since last scan
 */
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // Clear current matrix before scanning
    memset(current_matrix, 0, msize);

    // Scan each column
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        // Activate this column via GPIO
        select_col(col);

        // Read all rows for this column
        uint8_t row_state = read_rows();

        // Build the matrix by setting bits in the appropriate rows
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            // Extract bit for this row and place it in the correct column position
            current_matrix[row] |= ((row_state >> row) & 1) << col;
        }
    }

    // Deactivate all columns at end of scan
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        writePin(col_pins[col], 0);
    }

    // Check if matrix changed since last scan
    bool changed = (memcmp(current_matrix, prev_matrix, msize) != 0);

    // Save current state for next comparison
    memcpy(prev_matrix, current_matrix, msize);

    return changed;
}

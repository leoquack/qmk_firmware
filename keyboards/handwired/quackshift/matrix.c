// Copyright 2024 Leonidas Stratigakis (@Leonidas Stratigakis)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "wait.h"
#include "spi_master.h"

#if defined(CONSOLE_ENABLE)
#    include "print.h"
#endif

/*
 * Custom Matrix Implementation for SPI Shift Register
 *
 * This keyboard uses 74HC595 shift registers to drive the column selection.
 * The shift registers receive 16-bit values via SPI to activate specific columns,
 * while the rows are directly read from GPIO pins.
 *
 * Matrix scanning process:
 * 1. Send column selection pattern to shift register via SPI
 * 2. Wait for shift register outputs to settle
 * 3. Read all row pins to detect key presses in that column
 * 4. Repeat for all columns
 * 5. Compare with previous scan to detect changes
 */

// Column selection patterns sent to shift register (from config.h COLS)
static const uint16_t col_values[MATRIX_COLS] = COLS;

// Direct GPIO pins for row reading (from config.h ROWS)
static const pin_t row_pins[MATRIX_ROWS] = ROWS;

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
 * Select a column by sending its pattern to the shift register via SPI
 *
 * The 16-bit column value is sent as two bytes (MSB first) to the shift register.
 * After transmission, we wait for the shift register outputs to stabilize before
 * reading the row pins.
 *
 * @param col - Column index to select (0 to MATRIX_COLS-1)
 */
static inline void select_col(uint8_t col) {
    // Split 16-bit column value into two bytes for SPI transmission
    uint8_t message[2] = {
        (col_values[col] >> 8) & 0xFF,  // High byte
        col_values[col] & 0xFF           // Low byte
    };

    // Send column selection to shift register
    spi_start(SPI_COL_MATRIX_CS_PIN, SPI_lsbFirst, 0, SPI_DIVISOR);
    spi_transmit(message, 2);
    spi_stop();

    // Critical: Wait for shift register outputs to settle before reading rows
    matrix_io_delay();
}

/**
 * Initialize the matrix scanning hardware
 *
 * Sets up row pins as inputs with pull-down resistors, initializes SPI
 * for shift register communication, and configures the chip select pin.
 */
void matrix_init_custom(void) {
#if defined(CONSOLE_ENABLE)
    // Delay for USB serial connection when debugging
    wait_ms(1000);
#endif

    // Configure all row pins as inputs with pull-down
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        setPinInputLow(row_pins[row]);
    }
    matrix_io_delay();

    // Initialize SPI for shift register communication
    spi_init();
    matrix_io_delay();

    // Configure shift register chip select pin
    setPinOutput(SPI_COL_MATRIX_CS_PIN);
    matrix_io_delay();
}

/**
 * Scan the entire matrix and detect changes
 *
 * Iterates through all columns, activating each via shift register and reading
 * the corresponding row states. Compares the result with the previous scan to
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
        // Activate this column via shift register
        select_col(col);

        // Read all rows for this column
        uint8_t row_state = read_rows();

        // Build the matrix by setting bits in the appropriate rows
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            // Extract bit for this row and place it in the correct column position
            current_matrix[row] |= ((row_state >> row) & 1) << col;
        }
    }

    // Check if matrix changed since last scan
    bool changed = (memcmp(current_matrix, prev_matrix, msize) != 0);

    // Save current state for next comparison
    memcpy(prev_matrix, current_matrix, msize);

    return changed;
}

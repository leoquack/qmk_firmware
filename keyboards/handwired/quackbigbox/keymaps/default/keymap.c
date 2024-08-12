// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_2x7(
        KC_B, KC_V, KC_UP, KC_1, KC_2, KC_5, KC_6,
        KC_LEFT, KC_DOWN, KC_RIGHT, KC_3, KC_4, KC_7, KC_8
    ),
};

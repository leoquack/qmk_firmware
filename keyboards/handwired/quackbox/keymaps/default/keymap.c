// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM layer[] = {KC_6, KC_8, COMBO_END};
combo_t key_combos[] = {
    COMBO(layer, MO(1)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_2x6(
                  KC_UP, KC_1, KC_2, KC_5, KC_6,
        KC_LEFT, KC_DOWN, KC_RIGHT, KC_3, KC_4, KC_7, KC_8
    ),
    [1] = LAYOUT_2x6(
                  KC_UP, KC_A, KC_B, KC_ENTER, KC_NO,
        KC_LEFT, KC_DOWN, KC_RIGHT, KC_C, KC_D, KC_ESCAPE, KC_NO
    )
};


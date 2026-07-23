// Copyright 2024 Leonidas Stratigakis
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _NUMPAD,
    _DRAWING,
};

/*
 * NUM_MODE and ZERO_MODE are used on both layers so that their combo can
 * toggle drawing mode in either direction. When tapped separately, they send
 * Num Lock/0 on the numpad layer and F13/Space on the drawing layer.
 */
enum custom_keycodes {
    NUM_MODE = SAFE_RANGE,
    ZERO_MODE,
    ZOOM_OUT,
    ZOOM_IN,
};

const uint16_t PROGMEM drawing_toggle_combo[] = {ZERO_MODE, NUM_MODE, COMBO_END};

combo_t key_combos[] = {
    COMBO(drawing_toggle_combo, TG(_DRAWING)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │F1 │F2 │F3 │F4 │
     * ├───┼───┼───┼───┤
     * │Num│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │   0   │ . │   │
     * └───────┴───┴───┘
     *
     * Press 0 + Num together to toggle the drawing layer.
     */
    [_NUMPAD] = LAYOUT(
        KC_F1,    KC_F2,   KC_F3,   KC_F4,
        NUM_MODE, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,    KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,    KC_P5,   KC_P6,
        KC_P1,    KC_P2,   KC_P3,   KC_PENT,
        ZERO_MODE,         KC_PDOT
    ),

    /*
     * ┌──────────┬─────────┬───┬───┐
     * │Zoom out  │Zoom in  │ [ │ ] │
     * ├──────────┼─────────┼───┼───┤
     * │F13       │ E       │Pcl│ B │
     * ├──────────┼─────────┼───┼───┤
     * │Undo      │Redo     │F14│   │
     * ├──────────┼─────────┼───┤ I │
     * │Rotate (R)│Save     │F15│   │
     * ├──────────┼─────────┼───┼───┤
     * │Transform │Deselect │ L │   │
     * ├──────────┴─────────┼───┤Fit│
     * │Space / pan         │Tab│   │
     * └────────────────────┴───┴───┘
     */
    [_DRAWING] = LAYOUT(
        ZOOM_OUT,       ZOOM_IN,        KC_LBRC,         KC_RBRC,
        NUM_MODE,       KC_E,           C(S(KC_B)),      KC_B,
        C(KC_Z),        C(S(KC_Z)),     KC_F14,          KC_I,
        KC_R,           C(KC_S),        KC_F15,
        C(KC_T),        C(KC_D),        KC_L,            C(KC_0),
        ZERO_MODE,                                       KC_TAB
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NUM_MODE:
            if (record->event.pressed) {
                register_code16(IS_LAYER_ON(_DRAWING) ? KC_F13 : KC_NUM);
            } else {
                unregister_code16(IS_LAYER_ON(_DRAWING) ? KC_F13 : KC_NUM);
            }
            return false;

        case ZERO_MODE:
            if (record->event.pressed) {
                register_code16(IS_LAYER_ON(_DRAWING) ? KC_SPC : KC_P0);
            } else {
                unregister_code16(IS_LAYER_ON(_DRAWING) ? KC_SPC : KC_P0);
            }
            return false;

        case ZOOM_OUT:
        case ZOOM_IN:
            if (record->event.pressed) {
                register_mods(keycode == ZOOM_OUT ? MOD_BIT(KC_LALT) : MOD_BIT(KC_LCTL));
                register_code(KC_SPC);
                register_code16(MS_BTN1);
            } else {
                unregister_code16(MS_BTN1);
                unregister_code(KC_SPC);
                unregister_mods(keycode == ZOOM_OUT ? MOD_BIT(KC_LALT) : MOD_BIT(KC_LCTL));
            }
            return false;
    }

    return true;
}

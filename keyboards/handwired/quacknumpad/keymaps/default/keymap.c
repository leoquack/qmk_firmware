// Copyright 2024 Leonidas Stratigakis
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _NUMPAD,
    _DRAWING,
};

enum custom_keycodes {
    ZOOM_OUT = SAFE_RANGE,
    ZOOM_IN,
};

static bool     layer_switch_state;
static bool     layer_switch_last_read;
static uint32_t layer_switch_timer;

void keyboard_post_init_user(void) {
    setPinInputHigh(LAYER_SWITCH_PIN);

    layer_switch_state     = !readPin(LAYER_SWITCH_PIN);
    layer_switch_last_read = layer_switch_state;

    if (layer_switch_state) {
        layer_on(_DRAWING);
    } else {
        layer_off(_DRAWING);
    }
}

void matrix_scan_user(void) {
    bool switch_read = !readPin(LAYER_SWITCH_PIN);

    if (switch_read != layer_switch_last_read) {
        layer_switch_last_read = switch_read;
        layer_switch_timer     = timer_read32();
    }

    if (switch_read != layer_switch_state && timer_elapsed32(layer_switch_timer) > 20) {
        layer_switch_state = switch_read;

        if (layer_switch_state) {
            layer_on(_DRAWING);
        } else {
            layer_off(_DRAWING);
        }
    }
}

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
     */
    [_NUMPAD] = LAYOUT(
        KC_F1,  KC_F2,   KC_F3,   KC_F4,
        KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,  KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,  KC_P5,   KC_P6,
        KC_P1,  KC_P2,   KC_P3,   KC_PENT,
        KC_P0,            KC_PDOT
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
        KC_F13,         KC_E,           C(S(KC_B)),      KC_B,
        C(KC_Z),        C(S(KC_Z)),     KC_F14,          KC_I,
        KC_R,           C(KC_S),        KC_F15,
        C(KC_T),        C(KC_D),        KC_L,            C(KC_0),
        KC_SPC,                                          KC_TAB
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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

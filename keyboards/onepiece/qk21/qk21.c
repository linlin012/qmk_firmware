// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qk21.h"

#ifdef RGB_MATRIX_ENABLE
#define __ NO_LED
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  17,  18,  19,  20 },
  {  13,  14,  15,  16 },
  {  10,  11,  12,  __ },
  {  6,   7,   8,   9  },
  {  3,   4,   5,   __ },
  {  0,   __,  1,   2  }
},{
  // LED Index to Physical Position
  { 0,  0 },  { 37,  0 },  { 75,  0 },  { 112,  0 },
  { 0,  6 },  { 37,  6 },  { 75,  6 },  { 112,  6 },
  { 0,  13 }, { 37,  13 }, { 75,  13 },
  { 0,  19 }, { 37,  19 }, { 75,  19 }, { 112,  16 },
  { 0,  25},  { 37,  25},  { 75,  25 },
  { 18, 32 },              { 75,  32 }, { 75, 29 }

}, {
  // LED Index to Flag
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4
}};
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(NUM_LOCK_LED_INDEX)

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#    ifdef RGB_MATRIX_ENABLE
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            return false;
#    endif
    }
    return true;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    // RGB_MATRIX_INDICATOR_SET_COLOR(index, red, green, blue);

    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
    return true;
}

#endif  // NUM_LOCK_LED_INDEX

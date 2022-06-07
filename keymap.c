#include QMK_KEYBOARD_H

enum custom_keycodes {
    LCBR_CZ= SAFE_RANGE,
    RCBR_CZ,
    LSBR_CZ,
    RSBR_CZ,
    PIPE_CZ,
    BSLS_CZ,
    TILD_CZ,
    LESS_CZ,
    GRES_CZ,
    HACEK
};

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN, KC_TILD,
  _______, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_MPRV, KC_MPLY, KC_MNXT,/*half*/ _______, _______, KC_PIPE, LCBR_CZ, RCBR_CZ, LSBR_CZ, RSBR_CZ, _______,
                             KC_RALT, KC_MUTE, _______, _______, _______,  _______, KC_DEL, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   *  |   /  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | RAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_PPLS, KC_PMNS, KC_PSLS, KC_PAST, KC_PEQL, KC_PIPE,
  _______, _______, _______, _______, _______, _______,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, KC_PGDN,
  _______, TILD_CZ, BSLS_CZ, PIPE_CZ, LESS_CZ, GRES_CZ,  _______, _______,  _______, _______, KC_EQL,  HACEK,   _______, _______,
                             KC_RALT, _______, _______,  _______, _______,  _______, KC_DEL, KC_CAPS
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | RAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
//const char *read_logo(void);
//void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);
void write_jezko(void);

// const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    write_jezko();
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LCBR_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_LSFT);
            register_code(KC_LBRC);
        } else {
            unregister_code(KC_LBRC);
            unregister_code(KC_LSFT);
            unregister_code(KC_RALT);
        }
        break;
    case RCBR_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_LSFT);
            register_code(KC_RBRC);
        } else {
            unregister_code(KC_RBRC);
            unregister_code(KC_LSFT);
            unregister_code(KC_RALT);
        }
        break;
    case LSBR_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_LBRC);
        } else {
            unregister_code(KC_LBRC);
            unregister_code(KC_RALT);
        }
        break;
    case RSBR_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_RBRC);
        } else {
            unregister_code(KC_RBRC);
            unregister_code(KC_RALT);
        }
        break;
    case PIPE_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_LSFT);
            register_code(KC_BSLS);
        } else {
            unregister_code(KC_BSLS);
            unregister_code(KC_LSFT);
            unregister_code(KC_RALT);
        }
        break;
    case BSLS_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_BSLS);
        } else {
            unregister_code(KC_BSLS);
            unregister_code(KC_RALT);
        }
        break;
    case TILD_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_LSFT);
            register_code(KC_GRV);
        } else {
            unregister_code(KC_GRV);
            unregister_code(KC_LSFT);
            unregister_code(KC_RALT);
        }
        break;
    case LESS_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_COMM);
        } else {
            unregister_code(KC_COMM);
            unregister_code(KC_RALT);
        }
        break;
    case GRES_CZ:
        if (record->event.pressed) {
            register_code(KC_RALT);
            register_code(KC_DOT);
        } else {
            unregister_code(KC_DOT);
            unregister_code(KC_RALT);
        }
        break;
    case HACEK:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_EQL);
        } else {
            unregister_code(KC_EQL);
            unregister_code(KC_LSFT);
        }
        break;

    }
  return true;
}

void write_jezko() {
    static const char PROGMEM jezko[] = {
        	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf0,
	0xf0, 0xf8, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf0,
	0xf0, 0xf8, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf0,
	0xf0, 0xf8, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0xe0, 0xfc, 0xfc, 0xff, 0xff, 0x7f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff,
	0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x7f, 0xff, 0xff, 0xfc, 0xfc, 0xe0, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0xe0, 0xfc, 0xfc, 0xff, 0xff, 0x7f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff,
	0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x7f, 0xff, 0xff, 0xfc, 0xfc, 0xe0, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0xe0, 0xfc, 0xfc, 0xff, 0xff, 0x7f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff,
	0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x7f, 0xff, 0xff, 0xfc, 0xfc, 0xe0, 0x20, 0x00, 0x00,
	0x00, 0x12, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0x80, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x80,
	0x80, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x80, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x12, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x12, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0x80, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x80,
	0x80, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x80, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x12, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x12, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0x80, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x80,
	0x80, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x80, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x12, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x06, 0x0c, 0x0c, 0x18, 0x1b,
	0x1b, 0x18, 0x0c, 0x0c, 0x06, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x06, 0x0c, 0x0c, 0x18, 0x1b,
	0x1b, 0x18, 0x0c, 0x0c, 0x06, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x06, 0x0c, 0x0c, 0x18, 0x1b,
	0x1b, 0x18, 0x0c, 0x0c, 0x06, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(jezko, sizeof(jezko));
}


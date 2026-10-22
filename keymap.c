#include QMK_KEYBOARD_H

enum custom_keycodes {
    TOG_OS = SAFE_RANGE, // manual Linux <-> macOS switch
    // Czech symbols, see cz_map below
    LCBR_CZ,
    RCBR_CZ,
    LSBR_CZ,
    RSBR_CZ,
    PIPE_CZ,
    BSLS_CZ,
    TILD_CZ,
    LESS_CZ,
    GRES_CZ,
    HACEK,
    GRV_CZ,
    CIRC_CZ,
    LBRC_CZ,
    AT_CZ,
    HASH_CZ,
    DOLA_CZ,
    PERC_CZ,
    AMPR_CZ,
    SCLN_CZ,
    DEG_CZ,
    APOS_CZ,
    PSCR_CZ,
    CZ_LAST = PSCR_CZ
};

#define CZ_FIRST LCBR_CZ
#define CZ_COUNT (CZ_LAST - CZ_FIRST + 1)

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Host OS: auto-detected on plug-in (OS_DETECTION_ENABLE), TOG_OS overrides it
// until the next replug. Linux is the reference behaviour.
static bool is_mac    = false;
static bool os_manual = false;

static void set_os(bool mac) {
    is_mac = mac;
    // macOS: physical Ctrl sends Cmd (and GUI sends Ctrl) so Ctrl+C/V/... work
    // as on Linux. RAM only, not saved to EEPROM.
    keymap_config.swap_lctl_lgui = mac;
    keymap_config.swap_rctl_rgui = mac;
    clear_keyboard();
}

bool process_detected_host_os_user(os_variant_t os) {
    if (!os_manual && os != OS_UNSURE) {
        set_os(os == OS_MACOS || os == OS_IOS);
    }
    return true;
}

// Modifiers + key that type the same symbol on Linux "Czech (QWERTY)" and
// macOS "Czech - QWERTY". macOS combos are taken from QMK's
// quantum/keymap_extras/keymap_czech_mac_ansi.h.
typedef struct {
    uint8_t mods;
    uint8_t key;
} cz_combo_t;

#define M_ALTGR MOD_BIT(KC_RALT)
#define M_OPT   MOD_BIT(KC_LALT)
#define M_SFT   MOD_BIT(KC_LSFT)
#define M_CMD   MOD_BIT(KC_LGUI)

static const cz_combo_t PROGMEM cz_map[CZ_COUNT][2] = {
    //                         Linux                           macOS
    [LCBR_CZ - CZ_FIRST] = { { M_ALTGR | M_SFT, KC_LBRC }, { M_OPT, KC_9 } },        // {
    [RCBR_CZ - CZ_FIRST] = { { M_ALTGR | M_SFT, KC_RBRC }, { M_OPT, KC_0 } },        // }
    [LSBR_CZ - CZ_FIRST] = { { M_ALTGR, KC_LBRC },         { M_OPT, KC_LBRC } },     // [
    [RSBR_CZ - CZ_FIRST] = { { M_ALTGR, KC_RBRC },         { M_OPT, KC_RBRC } },     // ]
    // macOS: \ and | assume the keyboard type is set to ANSI (System Settings >
    // Keyboard > Change Keyboard Type). With ISO, macOS swaps KC_GRV and KC_NUBS.
    [PIPE_CZ - CZ_FIRST] = { { M_ALTGR | M_SFT, KC_BSLS }, { M_SFT, KC_GRV } },      // |
    [BSLS_CZ - CZ_FIRST] = { { M_ALTGR, KC_BSLS },         { 0, KC_GRV } },          // backslash
    [TILD_CZ - CZ_FIRST] = { { M_ALTGR | M_SFT, KC_GRV },  { M_OPT, KC_5 } },        // ~
    [LESS_CZ - CZ_FIRST] = { { M_ALTGR, KC_COMM },         { M_OPT, KC_COMM } },     // <
    [GRES_CZ - CZ_FIRST] = { { M_ALTGR, KC_DOT },          { M_OPT, KC_DOT } },      // >
    [HACEK   - CZ_FIRST] = { { M_SFT, KC_EQL },            { M_SFT, KC_EQL } },      // dead caron
    [GRV_CZ  - CZ_FIRST] = { { M_ALTGR, KC_GRV },          { M_SFT, KC_BSLS } },     // `
    [CIRC_CZ - CZ_FIRST] = { { M_ALTGR, KC_M },            { M_OPT, KC_6 } },        // ^
    [LBRC_CZ - CZ_FIRST] = { { M_SFT, KC_RBRC },           { M_SFT, KC_RBRC } },     // (
    [AT_CZ   - CZ_FIRST] = { { M_ALTGR, KC_2 },            { M_OPT, KC_2 } },        // @
    [HASH_CZ - CZ_FIRST] = { { M_ALTGR, KC_X },            { M_OPT, KC_3 } },        // #
    [DOLA_CZ - CZ_FIRST] = { { M_ALTGR, KC_4 },            { M_OPT, KC_4 } },        // $
    [PERC_CZ - CZ_FIRST] = { { M_ALTGR, KC_5 },            { M_SFT, KC_MINS } },     // %
    [AMPR_CZ - CZ_FIRST] = { { M_ALTGR, KC_7 },            { M_OPT, KC_7 } },        // &
    // Shift+; gives dead degree on Linux; handled in process_record_user on macOS
    [SCLN_CZ - CZ_FIRST] = { { 0, KC_GRV },                { M_OPT, KC_SCLN } },     // ;
    [DEG_CZ  - CZ_FIRST] = { { M_SFT, KC_GRV },            { M_OPT, KC_MINS } },     // dead degree
    [APOS_CZ - CZ_FIRST] = { { M_SFT, KC_BSLS },           { M_OPT, KC_QUOT } },     // '
    [PSCR_CZ - CZ_FIRST] = { { 0, KC_PSCR },               { M_CMD | M_SFT, KC_5 } }, // screenshot UI
};

// Combo sent on press, released on key up (survives an OS switch mid-press)
static cz_combo_t cz_held[CZ_COUNT];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY (US keycode labels, except the Czech ;/° key in the top right)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | ;/°  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   ú   |    |    )  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP|RCTRL |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 * On macOS, Ctrl and GUI are swapped (see set_os).
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SCLN_CZ,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_BSPC, KC_RCTL
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   {  |   }  |   [  |   ]  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ;  |   1  |   2  |   3  |   4  |   5  |-------.    ,-------|   6  |   7  |   8  |   9  |   0  |   °  |
 * |------+------+------+------+------+------|   ú   |    |    )  |------+------+------+------+------+------|
 * |      | VolD | VolU | Prev | Play | Next |-------|    |-------|  P+  |  P-  |  P/  |  P*  |  P=  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | RAlt | Mute |LOWER | /Space  /       \Enter \  |RAISE | Del  |RCTRL |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, _______, AT_CZ, HASH_CZ, DOLA_CZ, PERC_CZ,                       CIRC_CZ, AMPR_CZ, LCBR_CZ, RCBR_CZ, LSBR_CZ, RSBR_CZ,
  SCLN_CZ, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, DEG_CZ,
  _______, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,  _______, _______,  KC_PPLS, KC_PMNS, KC_PSLS, KC_PAST, KC_PEQL, _______,
                            KC_RALT, KC_MUTE, _______,   _______, _______,  _______, KC_DEL, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |   `  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |PrtSc |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | ;/°  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   @  |   #  |   $  |   %  |-------.    ,-------| Left | Down |  Up  |Right | PgUp | PgDn |
 * |------+------+------+------+------+------|       |    |   (   |------+------+------+------+------+------|
 * |      |   ~  |   \  |   |  |   <  |   >  |-------|    |-------|   `  |   ^  |   ´  |   ˇ  |   '  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | RAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | Del  | Caps |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 * PrtSc opens the screenshot UI on macOS (Cmd+Shift+5).
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, GRV_CZ,
  PSCR_CZ, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SCLN_CZ,
  _______, _______,   AT_CZ, HASH_CZ, DOLA_CZ, PERC_CZ,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, KC_PGDN,
  _______, TILD_CZ, BSLS_CZ, PIPE_CZ, LESS_CZ, GRES_CZ,  _______, LBRC_CZ,  GRV_CZ,  CIRC_CZ, KC_EQL,  HACEK,   APOS_CZ, _______,
                             KC_RALT, _______, _______,  _______, _______,  _______, KC_DEL, KC_CAPS
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  OS  |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------| Caps  |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | RAlt | Mute |LOWER | /Space  /       \Enter \  |RAISE | Del  | Caps |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 * OS: toggle Linux <-> macOS (overrides auto-detection until replug)
 */
  [_ADJUST] = LAYOUT(
  TOG_OS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
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
    oled_write_ln_P(is_mac ? PSTR("OS: macOS") : PSTR("OS: Linux"), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    write_jezko();
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == TOG_OS) {
        if (record->event.pressed) {
            os_manual = true;
            set_os(!is_mac);
        }
        return false;
    }

    if (keycode >= CZ_FIRST && keycode <= CZ_LAST) {
        cz_combo_t *held = &cz_held[keycode - CZ_FIRST];
        if (record->event.pressed) {
            const uint8_t shift = get_mods() & MOD_MASK_SHIFT;
            if (keycode == SCLN_CZ && is_mac && shift) {
                // macOS: Shift+; must give the dead degree, which is DEG_CZ
                // (Option+-) without Shift. Dead key, so a tap is enough.
                cz_combo_t deg;
                memcpy_P(&deg, &cz_map[DEG_CZ - CZ_FIRST][1], sizeof(deg));
                del_mods(shift);
                register_mods(deg.mods);
                tap_code(deg.key);
                unregister_mods(deg.mods);
                register_mods(shift);
                *held = (cz_combo_t){0, KC_NO};
            } else {
                memcpy_P(held, &cz_map[keycode - CZ_FIRST][is_mac], sizeof(*held));
                register_mods(held->mods);
                register_code(held->key);
            }
        } else {
            unregister_code(held->key);
            unregister_mods(held->mods);
        }
        return false;
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


/*
Copyright 2022 Dimitris Mantzouranis <d3xter93@gmail.com>
Copyright 2022 Pablo Ramirez
Copyright 2023 Santanu Paik (https://github.com/ITNerd69)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    WIN_BASE = 0,
    WIN_FN   = 1,
    MAC_BASE = 2,
    MAC_FN   = 3,
};
#define KC_TASK LGUI(KC_TAB)        // Task viewer
#define KC_FLXP LGUI(KC_E)          // Windows file explorer

#define KC_MSSN LGUI(KC_F3)         // Mission Control
#define KC_FIND LALT(LGUI(KC_SPC))  // Finder
#define KC_MSCR LSFT(LGUI(KC_3))    // Mac screenshot
#define KC_MSNP LSFT(LGUI(KC_4))    // Mac snip tool

// START TAP DANCE
enum {
	TD_2,
	TD_4,
	TD_E,
	TD_O,
	TD_S,
	TD_U,
};

void tap_dance_2(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		send_unicode_string("²");
	} else if (state->count == 2) {
		send_unicode_string("½");
	} else if (state->count >= 3) {
		send_unicode_string("÷");
	}
}

void tap_dance_4(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		send_unicode_string("€");
	} else if (state->count >= 2) {
		send_unicode_string("£");
	}
}

void tap_dance_e(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		send_unicode_string("é");
	} else if (state->count == 2) {
		send_unicode_string("è");
	} else if (state->count == 3) {
		send_unicode_string("É");
	} else if (state->count >= 4) {
		send_unicode_string("È");
	}
}

void tap_dance_o(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		send_unicode_string("ö");
	} else if (state->count >= 2) {
		send_unicode_string("Ö"); 
	}
}

void tap_dance_s(tap_dance_state_t *state, void *user_data) {
	if (state->count >= 1) {
		send_unicode_string("ß");
	}
}

void tap_dance_u(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		send_unicode_string("ü");
	} else if (state->count >= 2) {
		send_unicode_string("Ü");
	}
}

tap_dance_action_t tap_dance_actions[] = {
	[TD_2] = ACTION_TAP_DANCE_FN(tap_dance_2),
	[TD_4] = ACTION_TAP_DANCE_FN(tap_dance_4),
	[TD_E] = ACTION_TAP_DANCE_FN(tap_dance_e),
	[TD_O] = ACTION_TAP_DANCE_FN(tap_dance_o),
	[TD_S] = ACTION_TAP_DANCE_FN(tap_dance_s),
	[TD_U] = ACTION_TAP_DANCE_FN(tap_dance_u),
};
// END TAP DANCE

// START HOME ROW MODS
#define HM_A LGUI_T(KC_A)  // A acts as GUI (Cmd/Win) when held
#define HM_S LALT_T(KC_S)  // S acts as Alt when held
#define HM_D LSFT_T(KC_D)  // D acts as Shift when held
#define HM_F LCTL_T(KC_F)  // F acts as Ctrl when held

#define HM_J RCTL_T(KC_J)  // J acts as Ctrl when held
#define HM_K RSFT_T(KC_K)  // K acts as Shift when held
#define HM_L RALT_T(KC_L)  // L acts as Alt when held
#define HM_SCLN RGUI_T(KC_SCLN)  // ; acts as GUI (Cmd/Win) when held

uint8_t saved_rgb_mode = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case HM_A: case HM_S: case HM_D: case HM_F:
    case HM_J: case HM_K: case HM_L: case HM_SCLN:
      if (record->event.pressed && record->tap.count == 0) {
        if (rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_homerow_mods) {
          saved_rgb_mode = rgb_matrix_get_mode();
          rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_homerow_mods); // Set mods to be colored
        }
      } else if (!record->event.pressed) {
        rgb_matrix_mode_noeeprom(saved_rgb_mode);  // Reset mode
      }
      break;
  }
  return true;
}
// END HOME ROW MODS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*
    *****************************************************************************************************************
    * ESC  * F1   * F2   * F3   * F4   * F5   * F6   * F7   * F8   * F9   * F10  * F11  * F12  * PGUP * PSCR * RMOD *
    *****************************************************************************************************************
    * ~    * 1    * 2    * 3    * 4    * 5    * 6    * 7    * 8    * 9    * 0    * *    * =    * BSPC        * DEL  *
    *****************************************************************************************************************
    * TAB     * Q    * W    * E    * R    * T    * Y    * U    * I    * O    * P    * [    * ]    * \        * PGDN *
    *****************************************************************************************************************
    * CAPS      * A    * S    * D    * F    * G    * H    * J    * K    * L    * ;    * '    * ENT           * END  *
    *****************************************************************************************************************
    * LSFT         * Z    * X    * C    * V    * B    * N    * M    * ,    * .    * /    * RSFT       * UP   * HOME *
    *****************************************************************************************************************
    * LCTL  * LGUI  * LALT  * SPC                                         * RALT * FN   * RCTL * LEFT * DOWN * RGHT *
    *****************************************************************************************************************
  */
  [WIN_BASE] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_PGUP,    KC_PSCR,    RGB_MOD  ,
      KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,                KC_DEL   ,
      KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,                KC_PGDN  ,
      KC_CAPS,    HM_A,       HM_S,       HM_D,       HM_F,       KC_G,       KC_H,       HM_J,       HM_K,       HM_L,       HM_SCLN,    KC_QUOT,                KC_ENT,                 KC_END   ,
      KC_LSFT,                KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                KC_RSFT,    KC_UP,      KC_HOME  ,
      KC_LCTL,    KC_LGUI,    KC_LALT,                                        KC_SPC,                                         KC_RALT,    MO(WIN_FN),     KC_RCTL,    KC_LEFT,    KC_DOWN,    KC_RGHT
  ),

  /*
    *****************************************************************************************************************
    *RESET * BRID * BRIU * TASK * FLXP * RVAD * RVAI * MPRV * MPLY * MNXT * MUTE * VOLD * VOLU *      *  INS * RTOG *
    *****************************************************************************************************************
    *      *      * TD_2 *      * TD_4 *      *      *      *      *      *      * RSPD * RSPI *             *      *
    *****************************************************************************************************************
    *         *      *      * TD_E *      *      *      * TD_U *      * TD_O *      *      *      *          *      *
    *****************************************************************************************************************
    *           *      * TD_S *      *      *      *      *      *      *      *      *      *               *      *
    *****************************************************************************************************************
    *              *      *      *      *      *      *      *      *      *      *      *            * RSAI *      *
    *****************************************************************************************************************
    *       *       *       *                                             *      *      *      * RHUD * RSAD * RHUI *
    *****************************************************************************************************************
  */
  [WIN_FN] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      QK_BOOT,    KC_BRID,    KC_BRIU,    KC_TASK,    KC_FLXP,    RGB_VAD,    RGB_VAI,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,    KC_VOLD,    KC_VOLU,    _______,    KC_INS,     RGB_TOG  ,
      _______,    _______,    TD(TD_2),   _______,    TD(TD_4),   _______,    _______,    _______,    _______,    _______,    _______,    RGB_SPD,    RGB_SPI,    _______,                _______  ,
      _______,    _______,    _______,    TD(TD_E),   _______,    _______,    _______,    TD(TD_U),   _______,    TD(TD_O),   _______,    _______,    _______,    _______,                _______  ,
      _______,    _______,    TD(TD_S),   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,                _______  ,
      _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    RGB_SAI,    _______  ,
      _______,    _______,    _______,                                        _______,                                        _______,    _______,    _______,    RGB_HUD,    RGB_SAD,    RGB_HUI
  ),

    /*
    *****************************************************************************************************************
    * ESC  * F1   * F2   * F3   * F4   * F5   * F6   * F7   * F8   * F9   * F10  * F11  * F12  * PSCR * DEL  * RMOD *
    *****************************************************************************************************************
    * ~    * 1    * 2    * 3    * 4    * 5    * 6    * 7    * 8    * 9    * 0    * *    * =    * BSPC        * PGUP *
    *****************************************************************************************************************
    * TAB     * Q    * W    * E    * R    * T    * Y    * U    * I    * O    * P    * [    * ]    * \        * PGDN *
    *****************************************************************************************************************
    * CAPS      * A    * S    * D    * F    * G    * H    * J    * K    * L    * ;    * '    * ENT           * HOME *
    *****************************************************************************************************************
    * LSFT         * Z    * X    * C    * V    * B    * N    * M    * ,    * .    * /    * RSFT       * UP   * END  *
    *****************************************************************************************************************
    * LCTL  * LALT  * LGUI  * SPC                                         * LGUI * FN   * RCTL * LEFT * DOWN * RGHT *
    *****************************************************************************************************************
  */
  [MAC_BASE] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_MSCR,    KC_DEL,     RGB_MOD  ,
      KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,                KC_PGUP  ,
      KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,                KC_PGDN  ,
      KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                KC_ENT,                 KC_HOME  ,
      KC_LSFT,                KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                KC_RSFT,    KC_UP,      KC_END   ,
      KC_LCTL,    KC_LALT,    KC_LGUI,                                        KC_SPC,                                         KC_RGUI,    MO(MAC_FN), KC_RCTL,    KC_LEFT,    KC_DOWN,    KC_RGHT
  ),

  /*
    *****************************************************************************************************************
    *RESET * BRID * BRIU * TASK * FLXP * RVAD * RVAI * MPRV * MPLY * MNXT * MUTE * VOLD * VOLU *      *  INS * RTOG *
    *****************************************************************************************************************
    *      *      * TD_2 *      * TD_3 *      *      *      *      *      *      * RSPD * RSPI *             *      *
    *****************************************************************************************************************
    *         *      *      * TD_E *      *      *      * TD_U *      * TD_O *      *      *      *          *      *
    *****************************************************************************************************************
    *           *      * TD_S *      *      *      *      *      *      *      *      *      *               *      *
    *****************************************************************************************************************
    *              *      *      *      *      *      *      *      *      *      *      *            * RSAI *      *
    *****************************************************************************************************************
    *       *       *       *                                             *      *      *      * RHUD * RSAD * RHUI *
    *****************************************************************************************************************
  */
  [MAC_FN] = LAYOUT_ansi(
  /*  0           1           2           3           4           5           6           7           8           9           10          11          12          13          14          15       */
      QK_BOOT,      KC_BRID,    KC_BRIU,    KC_MSSN,    KC_FIND,    RGB_VAD,    RGB_VAI,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_MSNP,    KC_INS,     RGB_TOG  ,
      _______,    _______,    TD(TD_2),   _______,    TD(TD_4),   _______,    _______,    _______,    _______,    _______,    _______,    RGB_SPD,    RGB_SPI,    _______,                _______  ,
      _______,    _______,    _______,    TD(TD_E),   _______,    _______,    _______,    TD(TD_U),   _______,    TD(TD_O),   _______,    _______,    _______,    _______,                _______  ,
      _______,    _______,    TD(TD_S),   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,                _______  ,
      _______,                _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    RGB_SAI,    _______  ,
      _______,    _______,    _______,                                        _______,                                        _______,    _______,    _______,    RGB_HUD,    RGB_SAD,    RGB_HUI
  )
};

bool dip_switch_update_user(uint8_t index, bool active) {
  switch(index) {
    case 0: // OS switch
      if (active) { // Mac/iOS mode
        layer_move(MAC_BASE);
      }
      else { // Windows/Android mode
        layer_move(WIN_BASE);
      }
      break;
    case 1: // Connection switch
      // Probably it's not possible to do anything sensible here as switching from Cable to BT requires turning off the board. (BT / OFF / Cable)
      if (active) { // BT mode
        // do stuff
      }
      else { //Cable mode
        // do stuff
      }
      break;
  }
  return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable = true;
  // debug_matrix = true;
  // debug_keyboard = true;
  // debug_mouse = true;
}

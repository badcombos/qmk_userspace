#include QMK_KEYBOARD_H 

#include "config.h"
#include "layout.h"
#include "g/keymap_combo.h"
#include "features/casemodes.h"

static bool STATUS_ARROWS = false;

/*
 * -----------------------------------------------------------------------------------
 *  Key Overrides
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_key_overrides.md
 * -----------------------------------------------------------------------------------
*/
//shift backspace
const key_override_t override_key_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
	&override_key_delete,
	NULL // Null terminate the array of overrides!
};

void numlock_on(void) {
	led_t led_state = host_keyboard_led_state();
	bool b = led_state.num_lock;
	if (!b) {
		register_code(KC_NUM_LOCK);
		unregister_code(KC_NUM_LOCK);
	}
}
void keyboard_post_init_user() {
  numlock_on();
  STATUS_ARROWS = false;
}

// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case MOD_SPC:
			return 400;
		// case HRM_A:
		// 	return 400;
		default:
			return TAPPING_TERM;
	}
}

// returns true if key is overrided
// returns false if no processing takes place
bool override_helper(bool b, keyrecord_t *record, uint16_t keycode){
	if (b == true){
		if (record->event.pressed) {
			register_code(keycode);
			return true; 
		}
		unregister_code(keycode);
		return false;
	}
	return false;
}

/*
 * -----------------------------------------------------------------------------------
 *  Process User Record
 *  Where main keyboard logic goes
 * 
 *  return false = Skip all further processing of this key
 *  return true = Process keycodes normally
 * -----------------------------------------------------------------------------------
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	//for testing
	#ifdef CONSOLE_ENABLE
	xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.col, record->event.key.row, record->event.pressed);
	#endif

	// Process case modes
	if (!process_case_modes(keycode, record)) {
		return false;
	}

	static bool STATUS_RSHIFT = false; 
	static bool STATUS_RI_CASE = false; 

	if (STATUS_RI_CASE) {
		if (record->event.pressed) {
			switch (keycode) {
				case KC_A ... KC_Z:
					SEND_STRING(":regional_indicator_");
					tap_code16(keycode);
					SEND_STRING(": ");
					return false;
				case MOD_SPC:
					SEND_STRING("    ");
					return false;
				default: 
					STATUS_RI_CASE = false;
					return true;
			}
		}
	}

	switch (keycode) { 
		case C_CMETA: 
			STATUS_ARROWS = record->event.pressed;
			break;
		case KC_RSFT: 
			STATUS_RSHIFT = record->event.pressed;
			break;

		case KC_SLSH:
			if (!(get_mods() & MOD_BIT(KC_LSFT))) // if lshift is held, them dont unregister rshift
				unregister_code(KC_RSFT);
			return !(override_helper(STATUS_RSHIFT, record, KC_BACKSLASH));
		case KC_SCLN:
			if (!(get_mods() & MOD_BIT(KC_LSFT))) // if lshift is held, them dont unregister rshift
				unregister_code(KC_RSFT);
			return !(override_helper(STATUS_RSHIFT, record, KC_QUOT));

		case KC_E:
			return !(override_helper(STATUS_ARROWS, record, KC_UP));
		case KC_S:
			return !(override_helper(STATUS_ARROWS, record, KC_LEFT));
		case KC_D:
			return !(override_helper(STATUS_ARROWS, record, KC_DOWN));
		case KC_F:
			return !(override_helper(STATUS_ARROWS, record, KC_RIGHT));

		case C_SNAKECASE:
			if (record->event.pressed) {
				toggle_caps_word();
				enable_xcase_with(KC_UNDS);
			}
			return false;
		case C_NAVCASE:
			if (record->event.pressed) {
				enable_xcase_with(KC_SLSH);
			}
			return false;
		case C_RI_CASE:
			if (record->event.pressed) {
				STATUS_RI_CASE ^= 1; //xor boolean flip
				return false;
			}


	}//end switch
	
	return true;
}

/*
 * -----------------------------------------------------------------------------------
 *  only allow combos on the base layer
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_combo.md
 * -----------------------------------------------------------------------------------
*/
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
	if (layer_state_is(_BASE)) { 
		return true; 
	}
	return false;
}

// /*
//  * -----------------------------------------------------------------------------------
//  *  Caps Word
//  *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_caps_word.md
//  * -----------------------------------------------------------------------------------
// */
// bool caps_word_press_user(uint16_t keycode) {
// 	switch (keycode) {
// 		// Keycodes that continue Caps Word, with shift applied.
// 		case KC_A ... KC_Z:
// 		case KC_MINS:
// 			add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
// 			return true;

// 		// Keycodes that continue Caps Word, without shifting.
// 		case KC_1 ... KC_0:
// 		case MOD_SPC:
// 		case KC_BSPC:
// 		case KC_DEL:
// 		case KC_UNDS:
// 			return true;

// 		default:
// 			return false;  // Deactivate Caps Word.
// 	}
// }

/*
 * -----------------------------------------------------------------------------------
 *  Leader Key
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_leader_key.md
 * -----------------------------------------------------------------------------------
*/
LEADER_EXTERNS();

void matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		leading = false;
		leader_end();

		SEQ_FOUR_KEYS(KC_B, KC_O, KC_O, KC_T) {
			tap_code16(QK_BOOT);
		}
		SEQ_ONE_KEY(KC_S) {
			SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_LEFT))));
		}
	}
}

/*
 * -----------------------------------------------------------------------------------
 *  Tap Dance
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_tap_dance.md
 * -----------------------------------------------------------------------------------
*/
 
//ALT_TAB definitions
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

//td space definitions 
int tapState_space = 0;

enum {
	SINGLE_TAP = 1,
	SINGLE_HOLD = 2,
	DOUBLE_TAP = 3,
	DOUBLE_HOLD = 4,
	TRIPLE_TAP = 5,
	TRIPLE_HOLD = 6
};

int tapState (qk_tap_dance_state_t *state) {
	switch (state->count) {
		case 1: 
			return (state->pressed)? SINGLE_HOLD : SINGLE_TAP;
		case 2:
			return (state->pressed)? DOUBLE_HOLD : DOUBLE_TAP;
		case 3:
			return (state->pressed)? TRIPLE_TAP : TRIPLE_HOLD;
		default:
			return 8;
	}
}


void space_finished (qk_tap_dance_state_t *state, void *user_data) {
	tapState_space = tapState(state);

	switch (tapState_space) {
		case SINGLE_TAP: 
			tap_code(KC_SPC);
			reset_tap_dance (state);
			break;
		case SINGLE_HOLD: 
			register_code(KC_LCTL); 
			break;
		case DOUBLE_TAP: 
			tap_code(KC_TAB);
			break;
	} 
}

void space_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (tapState_space) {
		case SINGLE_TAP: 
			break;
		case SINGLE_HOLD: 
			unregister_code(KC_LCTL); 
			break;
		case DOUBLE_TAP: 
			break;
		}
	tapState_space = 0;
}

void td_parenthesis (qk_tap_dance_state_t *state, void *user_data) {
	int taps = tapState(state);

	switch (taps){
		case SINGLE_TAP:
			SEND_STRING ("()" SS_TAP(X_LEFT));
			reset_tap_dance (state);
			break;
		case DOUBLE_TAP:
			SEND_STRING ("[]" SS_TAP(X_LEFT));
			break;
	}
}

void td_tab (qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (is_alt_tab_active == true) { //tapping tap refreshes the timer
			alt_tab_timer = timer_read();
		}
		register_code(KC_TAB);
		reset_tap_dance (state); 
	}
	else if (state->count == 2) { 
		if (!is_alt_tab_active) {
			is_alt_tab_active = true;
			register_code(KC_LALT);
		}
		alt_tab_timer = timer_read();
		register_code(KC_TAB);
	}
	// 	
	unregister_code(KC_TAB);
}

void p_finished (qk_tap_dance_state_t *state, void *user_data) {
	int taps = tapState(state);

	switch (taps){
		case SINGLE_TAP:
			tap_code(KC_P);
			reset_tap_dance (state);
			break;
		case SINGLE_HOLD:
			STATUS_ARROWS = true;
			register_mods(MOD_BIT(KC_LCTL));
			register_mods(MOD_BIT(KC_LGUI));
			break;
	}
}

void p_reset (qk_tap_dance_state_t *state, void *user_data) {
	unregister_mods(MOD_BIT(KC_LCTL));
	unregister_mods(MOD_BIT(KC_LGUI));
	STATUS_ARROWS = false;
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_TAB] = ACTION_TAP_DANCE_FN(td_tab),

	[TD_PAR] = ACTION_TAP_DANCE_FN(td_parenthesis),

	// [UKC_SPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space_finished, space_reset),

	[TD_P] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, p_finished, p_reset),
};
#include QMK_KEYBOARD_H 

#include "config.h"
#include "layout.h"
#include "g/keymap_combo.h"

/*
 * -----------------------------------------------------------------------------------
 *  Key Overrides
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_key_overrides.md
 * -----------------------------------------------------------------------------------
*/

//shift backspace
const key_override_t override_key_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

//alt nums for function keys
// const key_override_t override_key_1 = ko_make_basic(MOD_MASK_ALT, KC_1, KC_F1);
// const key_override_t override_key_2 = ko_make_basic(MOD_MASK_ALT, KC_2, KC_F2);
// const key_override_t override_key_3 = ko_make_basic(MOD_MASK_ALT, KC_3, KC_F3);
// const key_override_t override_key_4 = ko_make_basic(MOD_MASK_ALT, KC_4, KC_F4);
// const key_override_t override_key_5 = ko_make_basic(MOD_MASK_ALT, KC_5, KC_F5);
// const key_override_t override_key_6 = ko_make_basic(MOD_MASK_ALT, KC_6, KC_F6);
// const key_override_t override_key_7 = ko_make_basic(MOD_MASK_ALT, KC_7, KC_F7);
// const key_override_t override_key_8 = ko_make_basic(MOD_MASK_ALT, KC_8, KC_F8);
// const key_override_t override_key_9 = ko_make_basic(MOD_MASK_ALT, KC_9, KC_F9);

const key_override_t **key_overrides = (const key_override_t *[]){
	&override_key_delete,
	//
	// &override_key_1,
	// &override_key_2,
	// &override_key_3,
	// &override_key_4,
	// &override_key_5,
	// &override_key_6,
	// &override_key_7,
	// &override_key_8,
	// &override_key_9,
	NULL // Null terminate the array of overrides!
};

//custom overrides
unsigned char nav_state = 0;
const unsigned char nav_state_max = 1;

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

// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case MOD_SPC:
			return 400;
		case HRM_A:
			return 400;
		default:
			return TAPPING_TERM;
	}
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
		switch (keycode) { 
		// case KC_E:
		// 	return !(override_helper(nav_state == 1, record, KC_UP) || 
		// 			 override_helper(nav_state == 2, record, KC_PAGE_UP) ||
		// 			 override_helper(nav_state == 3, record, KC_VOLU));
		// case KC_S:
		// 	return !(override_helper(nav_state == 1, record, KC_LEFT) || 
		// 			 override_helper(nav_state == 2, record, KC_HOME) ||
		// 			 override_helper(nav_state == 3, record, KC_MPRV));
		// case KC_D:
		// 	return !(override_helper(nav_state == 1, record, KC_DOWN) || 
		// 			 override_helper(nav_state == 2, record, KC_PAGE_DOWN) ||
		// 			 override_helper(nav_state == 3, record, KC_VOLD));
		// case KC_F:
		// 	return !(override_helper(nav_state == 1, record, KC_RIGHT) || 
		// 			 override_helper(nav_state == 2, record, KC_END) ||
		// 			 override_helper(nav_state == 3, record, KC_MNXT));
		
		// case MOD_SPC: //not KC_SPC because using taphold function on space
		// 	return !(override_helper(nav_state == 3, record, KC_MPLY));
		// 	//KC_HYPR ,KC_MEH  ,KC_GC   ,		  KC_DEL  ,_______ , KC_ENT

		case C_TOGGLE:
			if (record->event.pressed) {
				nav_state = (nav_state < nav_state_max)? nav_state+1: 0;
				return false;
			}

		}//end switch
	
	return true;
}

/*
 * -----------------------------------------------------------------------------------
 *  Tri Layout Toggle
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/ref_functions.md
 * -----------------------------------------------------------------------------------
*/
layer_state_t layer_state_set_user(layer_state_t state) {
	state = update_tri_layer_state(state, _NAV, _NUM, _ADJ);

	#ifdef IS_PLANCK
	/*
	 * -----------------------------------------------------------------------------------
	 *  Planck RGB UnderGlow
	 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md
	 * -----------------------------------------------------------------------------------
	*/
		// bool is_qwerty = true;

		switch (get_highest_layer(state)) {
			case _NAV:
				rgblight_setrgb(RGB_RED);
				break;
			case _NUM:
				rgblight_setrgb(RGB_CYAN);
				break;
			case _ADJ:
				rgblight_setrgb(RGB_PURPLE);
				break;
			default: //for any other layers, or the default layer
				rgblight_setrgb(RGB_GREEN);
				// is_qwerty ? rgblight_setrgb(RGB_GREEN) : rgblight_setrgb(RGB_BLUE) ;
				break;
		}
	#endif 

	return state;
}

/*
 * -----------------------------------------------------------------------------------
 *  fixes rgb being a different color on startup because it uses the last 'saved color'
 *  https://docs.qmk.fm/#/custom_quantum_functions?id=keyboard-post-initialization-code
 * -----------------------------------------------------------------------------------
*/
#ifdef IS_PLANCK
void keyboard_post_init_user(void) {
	rgblight_enable_noeeprom(); // enables Rgb, without saving settings
	rgblight_sethsv_noeeprom(HSV_GREEN); // sets the color to teal/cyan without saving
}
#endif

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

#ifdef OLED_ENABLE
bool oled_task_user(void) {
	
	// Host Keyboard Layer Status
	oled_write_P(PSTR("Layer: "), false);

	/*
	 * -----------------------------------------------------------------------------------
	 *  trigger on layer change AND default layer change from:
	 *  https://www.reddit.com/r/olkb/comments/o5924u/comment/h2pq9rd/?utm_source=share&utm_medium=web2x&context=3
	 * -----------------------------------------------------------------------------------
	*/
	switch (get_highest_layer(layer_state|default_layer_state)) {
		case _BASE:
			oled_write_P(PSTR("BASE-QWERTY\n"), false);
			break;
		case _GAME:
			oled_write_P(PSTR("BASE-GAMING\n"), false);
			break;
		case _NAV:
			oled_write_P(PSTR("NAVIGATION\n"), false);
			break;
		case _NUM:
			oled_write_P(PSTR("NUMBERS\n"), false);
			break;
		case _ADJ:
			oled_write_P(PSTR("SETTINGS\n"), false);
			break;            
		default:
			// Or use the write_ln shortcut over adding '\n' to the end of your string
			oled_write_ln_P(PSTR("Undefined"), false);
	}

	// Host Keyboard LED Status
	led_t led_state = host_keyboard_led_state();
	oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
	oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
	oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	
	return false;
	
}
#endif //oled enable ifdef

/*
 * -----------------------------------------------------------------------------------
 *  Tap Dance
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_tap_dance.md
 * -----------------------------------------------------------------------------------
*/

//ALT_TAB definitions
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

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

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_TAB] = ACTION_TAP_DANCE_FN(td_tab),

	[TD_PAR] = ACTION_TAP_DANCE_FN(td_parenthesis),

	// [UKC_SPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space_finished, space_reset),
};
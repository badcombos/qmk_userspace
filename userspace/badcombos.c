#include QMK_KEYBOARD_H 

#include "config.h"
#include "layout.h"

// struct to keep track of which "nav mode" we want
typedef struct {
	bool arrows;
	bool alt_nav;
	bool volume;
} nav_mode_struct;

static nav_mode_struct nav_mode;

// what keys to replace overridden key with
struct overrides {
	uint16_t arrow_key;
	uint16_t alt_nav_key;
	uint16_t volume_key;
};

const static struct overrides UP_OVERRIDE 		= {KC_UP   , KC_PGUP, KC_VOLU };
const static struct overrides DOWN_OVERRIDE 	= {KC_DOWN , KC_PGDN, KC_VOLD };
const static struct overrides LEFT_OVERRIDE 	= {KC_LEFT , KC_HOME, KC_MPRV };
const static struct overrides RIGHT_OVERRIDE 	= {KC_RIGHT, KC_END , KC_MNXT };

/*
 * -----------------------------------------------------------------------------------
 *  Key Overrides
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_key_overrides.md
 * -----------------------------------------------------------------------------------
*/
//shift backspace
const key_override_t override_key_delete = ko_make_basic(MOD_MASK_GUI, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]) {
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
void keyboard_post_init_user() { // function runs on keyboard startup
	numlock_on();

	nav_mode.arrows = false;
	nav_mode.alt_nav = false;
	nav_mode.volume = false;
}

// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case C_SPAC:
			return 400;
		default:
			return TAPPING_TERM;
	}
}

// returns true if key is overrided
// returns false if no processing takes place
bool override_helper(keyrecord_t *record, struct overrides override){

	uint16_t keycode = KC_NO;

	if (nav_mode.arrows == true) {
		keycode = override.arrow_key;
	}
	if (nav_mode.alt_nav == true) {
		keycode = override.alt_nav_key;
	}
	if (nav_mode.volume == true) {
		keycode = override.volume_key;
	}

	if (keycode == KC_NO){
		return false;
	}
	
	if (record->event.pressed) {
		register_code(keycode);
		return true; 
	}
	unregister_code(keycode);
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
	xprintf("KL: row: %u, column: %u, pressed: %u\n", 
		record->event.key.col, record->event.key.row, record->event.pressed);
	#endif
// #ifdef CONSOLE_ENABLE
// 	uprintf("0x%04X\t%u\t%u\t0x%X\t%b\t0x%02X\t0x%02X\t%u\n",
// 		keycode,
// 		record->event.key.row,
// 		record->event.key.col,
// 		layer_state|default_layer_state,
// 		record->event.pressed,
// 		get_mods(),
// 		get_oneshot_mods(),
// 		record->tap.count
// 		);
// #endif

	// Process case modes
	if (!process_case_modes(keycode, record)) {
		return false;
	}
 
	switch (keycode) { 
		case KC_E:
			return !(override_helper(record, UP_OVERRIDE));
		case KC_S:
			return !(override_helper(record, LEFT_OVERRIDE));
		case KC_D:
			return !(override_helper(record, DOWN_OVERRIDE));
		case KC_F:
			return !(override_helper(record, RIGHT_OVERRIDE));

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
		// case C_RI_CASE:
		// 	if (record->event.pressed) {
		// 		STATUS_RI_CASE ^= 1; //xor boolean flip
		// 		return false;
		// 	}


	}//end switch
	
	return true;
}

/*
 * -----------------------------------------------------------------------------------
 *  only allow combos on the base layer
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_combo.md
 * -----------------------------------------------------------------------------------
*/
#ifdef CONSOLE_ENABLE
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
	if (layer_state_is(_BASE)) { 
		return true; 
	}
	return false;
}
#endif

/*
 * -----------------------------------------------------------------------------------
 *  Caps Word
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_caps_word.md
 * -----------------------------------------------------------------------------------
*/
bool caps_word_press_user(uint16_t keycode) {
	switch (keycode) {
		// Keycodes that continue Caps Word, with shift applied.
		case KC_A ... KC_Z:
		case KC_MINS:
			add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
			return true;

		// Keycodes that continue Caps Word, without shifting.
		case KC_1 ... KC_0:
		case C_SPAC:
		case KC_BSPC:
		case KC_DEL:
		case KC_UNDS:
			return true;

		default:
			return false;  // Deactivate Caps Word.
	}
}

/*
 * -----------------------------------------------------------------------------------
 *  Leader Key
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_leader_key.md
 * -----------------------------------------------------------------------------------
*/
void leader_start_user(void) {
	// Do something when the leader key is pressed
}

void leader_end_user(void) {
	if (leader_sequence_two_keys(KC_S, KC_S)) {
		SEND_STRING(SS_LGUI(SS_LSFT("s"))); //screenshot
	}
	else if (leader_sequence_three_keys(KC_G, KC_I, KC_F)) {
		SEND_STRING("https://tenor.com/view/funny-gif-21510495"); // i has gif meme
	}
	else if (leader_sequence_four_keys(KC_B, KC_O, KC_O, KC_T)) {
		reset_keyboard(); //enter bootloader
	}
	else if (leader_sequence_four_keys(KC_P, KC_I, KC_P, KC_E)) { 
		SEND_STRING("https://tenor.com/view/bomb-bruh-mailbox-jump-jumping-gif-18537429"); // pipebomb meme
	}
	else if (leader_sequence_four_keys(KC_H, KC_O, KC_L, KC_D)) { 
		SEND_STRING("https://i.redd.it/m5gua7s3jcna1.png"); // :3 meme
	}
	else if (leader_sequence_four_keys(KC_T, KC_A, KC_L, KC_K)) { 
		SEND_STRING("https://media.discordapp.net/attachments/695076990075535461/821450127801319444/Woman.gif"); // talking meme
	}
	else if (leader_sequence_five_keys(KC_C, KC_L, KC_E, KC_A, KC_R)) {
		eeconfig_init(); //clear eeprom
	}
}



/*
 * -----------------------------------------------------------------------------------
 *  Tap Dance
 *  https://github.com/qmk/qmk_firmware/blob/master/docs/feature_tap_dance.md
 * -----------------------------------------------------------------------------------
*/

#ifdef TAP_DANCE_ENABLE

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

int tapState (tap_dance_state_t *state) {
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

void td_parenthesis (tap_dance_state_t *state, void *user_data) {
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

void td_tab (tap_dance_state_t *state, void *user_data) {
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

void nav_finished (tap_dance_state_t *state, void *user_data) {
	int taps = tapState(state);

	switch (taps){
		case SINGLE_TAP:
			break;
		case SINGLE_HOLD:
			nav_mode.arrows = true;
			break;
		case DOUBLE_HOLD:
			nav_mode.alt_nav = true;
			break;
	}
}

void nav_reset (tap_dance_state_t *state, void *user_data) {
	nav_mode.arrows = false;
	nav_mode.alt_nav = false;
}

tap_dance_action_t tap_dance_actions[] = {

	[TD_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_finished, nav_reset),

	// [TD_TAB] = ACTION_TAP_DANCE_FN(td_tab),
	// [TD_PAR] = ACTION_TAP_DANCE_FN(td_parenthesis),
};

#endif
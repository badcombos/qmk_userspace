#pragma once

/* 
 * custom keycodes
 * -----------------------------------------------------------------------------------
 * Because the use of SAFE_RANGE to enumerate custom keycodes is not supported inside config.h, we manually count up from a high number
 * read more about the issue here: https://filterpaper.github.io/qmk/userspace#limitations 
 * -----------------------------------------------------------------------------------
 * keycode list in hex found at the link below
 * https://github.com/qmk/qmk_firmware/blob/master/quantum/keycodes.h
 */
#define C_SAFE_RANGE 		0xff00 //qmk SAFE_RANGE = 0x7E00
//0x8000 - 0xFFFF are reserved for unicode, dont use if using unicode
#define C_TOGGLE_MACROS 	0xff01
#define C_SNAKECASE  		0xff02
#define C_NAVCASE 			0xff04
#define C_RI_CASE	 		0xff05

// Tap Dance declarations
#define TD_TAB 				0
#define TD_PAR 				1

// Layers
#define _BASE 				0
#define _NAV 				1
#define _NUM 				2

// Layer keys
#define L_NAV           	MO(_NAV)
#define L_NUM           	MO(_NUM)

#define L_SLASH           	LT(_NUM, KC_SLSH)

//custom macros
#define MOD_SPC 			LCTL_T(KC_SPC)
#define MOD_BSPC 			LSFT_T(KC_BSPC)
#define MOD_P 				MT(MOD_LCTL | MOD_LGUI, KC_P)

#define C_CMETA 			LGUI(KC_LCTL)

//combo macros
// #define C_LDESK 			LGUI(LCTL(KC_LEFT))
// #define C_RDESK 			LGUI(LCTL(KC_RIGHT))

#define C_STAB 				LSFT(KC_TAB)

//KC_GRV KC_EXLM KC_AT KC_HASH KC_DLR KC_PERC KC_CIRC KC_AMPR KC_ASTR
// KC_LPRN KC_RPRN
// KC_LCBR KC_RCBR
// KC_LBRC KC_RBRC
// KC_MINS KC_UNDS KC_BACKSLASH KC_EQL KC_PLUS
//KC_F11  KC_F12

//` ~ ! @ # $ % ^ & * ( ) - _ = + [ ] { } \ | ; : ' " , < . > / ?

// COMB(lbrace_combo,		KC_LBRC,		KC_M, KC_COMM)
// COMB(rbrace_combo,		KC_RBRC,		KC_COMM, KC_DOT)

// Layout Aliases
#define LAYOUT_willy_wrapper(...) LAYOUT(__VA_ARGS__)

#define LAYOUT_oxymoron_wrapper(...) LAYOUT(__VA_ARGS__)

#define LAYOUT_mini36_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

#define LAYOUT_planck_wrapper(...) LAYOUT_planck_2x2u(__VA_ARGS__)


#define BASE \
/* ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐ */ \
	  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  , MOD_P  ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,  KC_N  ,  KC_M  ,KC_COMM , KC_DOT ,L_SLASH ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	                  KC_LGUI , KC_NO  ,MOD_SPC ,MOD_BSPC, KC_NO  ,L_NAV                          \
/*                   └────────┴─────────────────┴─────────────────┴────────┘                   */ 

#define NUM \
/* ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐ */ \
	KC_EXLM , KC_AT  ,KC_HASH , KC_DLR ,KC_PERC ,KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LCBR ,KC_RCBR ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LBRC ,KC_RBRC ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	                  _______ ,_______ ,_______ ,_______ ,_______ ,_______                        \
/*                   └────────┴─────────────────┴─────────────────┴────────┘                   */ 

#define NAV \
/* ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐ */ \
	XXXXXXX ,KC_HOME , KC_UP  , KC_END ,KC_PGUP ,XXXXXXX ,KC_MPLY ,KC_VOLU ,XXXXXXX ,XXXXXXX ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	KC_GRAVE,KC_LEFT ,KC_DOWN ,KC_RIGHT,KC_PGDN ,XXXXXXX ,KC_MPRV ,KC_VOLD ,KC_MNXT ,XXXXXXX ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	C(KC_Z) ,C(KC_X) ,C(KC_C) ,C(KC_V) ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	                  _______ ,_______ ,_______ ,_______ ,_______ ,_______                        \
/*                   └────────┴─────────────────┴─────────────────┴────────┘                   */ 

// Convert 3x10_6 unibody to oxymoron staggered
#define CONV_OXYMORON(k) K36_TO_OXYMORON(k)
#define K36_TO_OXYMORON( \
/* ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐ */ \
	l01 ,l02 ,l03 ,l04 ,l05 ,r01 ,r02 ,r03 ,r04 ,r05 ,    \
/* ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤ */ \
	l06 ,l07 ,l08 ,l09 ,l10 ,r06 ,r07 ,r08 ,r09 ,r10 ,    \
/* ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤ */ \
	l11 ,l12 ,l13 ,l14 ,l15, r11 ,r12 ,r13 ,r14 ,r15 ,    \
/* └────┴────┴────┼────┼────┼────┼────┼────┼────┼────┤ */ \
				   l16 ,l17 ,l18 ,r16 ,r17 , r18          \
/*				  └────┴────┴────┴────┴────┴────┘      */ \
) \
/* ┌───────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───┬───────┐ */ \
	KC_ESC ,l01 ,l02 ,l03 ,l04 ,l05 ,r01 ,r02 ,r03 ,r04 ,r05,KC_BSPC,    \
/* ├───────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──┴┐      | */ \
	KC_TAB  ,l06 ,l07 ,l08 ,l09 ,l10 ,r06 ,r07 ,r08 ,r09 ,r10, KC_NO,    \
/* ├──────┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬┴──────┤ */ \
	L_NUM ,l11 ,l12 ,l13 ,l14 ,l15, r11 ,r12 ,r13 ,r14 ,r15 ,KC_RSFT,    \
/* ├──────┴┬───┴───┬┴────┴────┴────┴────┴────┴────┴─┬──┴────┴┬──────┤ */ \
	KC_LCTL,KC_LGUI,KC_NO, KC_NO, MOD_SPC, KC_NO    ,L_NAV ,KC_NO, C_CMETA \
/* └───────┴───────┴────────────────────────────────┴────────┴──────┘  */

// Convert 3x10_6 unibody to 3x5_3 split
#define CONV_SPLIT36(k) K36_TO_SPLIT36(k)
#define K36_TO_SPLIT36( \
/* ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐ */ \
	l01 ,l02 ,l03 ,l04 ,l05 ,r01 ,r02 ,r03 ,r04 ,r05 ,    \
/* ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤ */ \
	l06 ,l07 ,l08 ,l09 ,l10 ,r06 ,r07 ,r08 ,r09 ,r10 ,    \
/* ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤ */ \
	l11 ,l12 ,l13 ,l14 ,l15, r11 ,r12 ,r13 ,r14 ,r15 ,    \
/* └────┴────┴────┼────┼────┼────┼────┼────┼────┼────┤ */ \
				   l16 ,l17 ,l18 ,r16 ,r17 , r18          \
/*				  └────┴────┴────┴────┴────┴────┘      */ \
)\
/* ┌────┬────┬────┬────┬────┐				 ┌────┬────┬────┬────┬────┐ */ \
	l01 ,l02 ,l03 ,l04 ,l05 ,				  r01 ,r02 ,r03 ,r04 ,r05 ,    \
/* ├────┼────┼────┼────┼────┤				 ├────┼────┼────┼────┼────┤ */ \
	l06 ,l07 ,l08 ,l09 ,l10 ,				  r06 ,r07 ,r08 ,r09 ,r10 ,    \
/* ├────┼────┼────┼────┼────┤				 ├────┼────┼────┼────┼────┤ */ \
	l11 ,l12 ,l13 ,l14 ,l15,             	  r11 ,r12 ,r13 ,r14 ,r15 ,    \
/* └────┴────┴────┼────┼────┼────┐		┌────┼────┴────┼────┴────┴────┘ */ \
				   l16 ,l17 ,l18 ,		 r16 ,r17 , r18                    \
/*				  └────┴────┴────┘		└────┴────┴────┘ 				*/ \

// Convert 3x10_6 to 4x12
#define CONV_PLANCK(k) K36_TO_PLANCK(k)
#define K36_TO_PLANCK( \
/* ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐ */ \
	l01 ,l02 ,l03 ,l04 ,l05 ,r01 ,r02 ,r03 ,r04 ,r05 ,    \
/* ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤ */ \
	l06 ,l07 ,l08 ,l09 ,l10 ,r06 ,r07 ,r08 ,r09 ,r10 ,    \
/* ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤ */ \
	l11 ,l12 ,l13 ,l14 ,l15, r11 ,r12 ,r13 ,r14 ,r15 ,    \
/* └────┴────┴────┼────┼────┼────┼────┼────┼────┼────┤ */ \
				   l16 ,l17 ,l18 ,r16 ,r17 , r18          \
/*				  └────┴────┴────┴────┴────┴────┘      */ \
)\
/* ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐ */ \
	KC_ESC  ,  l01   ,  l02   ,  l03   ,  l04   ,  l05   ,  r01   ,  r02   ,  r03   ,  r04   ,  r05   ,KC_BSPC ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	KC_TAB  ,  l06   ,  l07   ,  l08   ,  l09   ,  l10   ,  r06   ,  r07   ,  r08   ,  r09   ,  r10   ,KC_QUOT ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
	KC_LSFT ,  l11   ,  l12   ,  l13   ,  l14   ,  l15   ,  r11   ,  r12   ,  r13   ,  r14   ,  r15   ,KC_ENT  ,    \
/* ├────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┼────────┼────────┼────────┤ */ \
	KC_LCTL ,KC_LALT ,KC_LGUI ,  l17   ,       l18       ,       r16       ,   r17  ,C_LDESK ,C_RDESK ,KC_ENT       \
/* └────────┴────────┴────────┴────────┴─────────────────┴─────────────────┴────────┴────────┴────────┴────────┘ */ \


#pragma once

/* 
 * custom keycodes
 * -----------------------------------------------------------------------------------
 * Because the use of SAFE_RANGE to enumerate custom keycodes is not supported 
 * inside config.h, we manually count up from a high number
 * read more about the issue here: https://filterpaper.github.io/qmk/userspace#limitations 
 * -----------------------------------------------------------------------------------
 * keycode list in hex found at the link below
 * https://github.com/qmk/qmk_firmware/blob/master/quantum/keycodes.h
 * -----------------------------------------------------------------------------------
 */
#define C_SAFE_RANGE        0x7E00 //qmk SAFE_RANGE = 0x7E00
//0x8000 - 0xFFFF are reserved for unicode
#define C_TOGGLE_MACROS     0x7E01
#define C_SNAKECASE         0x7E02
#define C_NAVCASE           0x7E04
#define C_RI_CASE           0x7E05

//define character aliases to make keyboard ascii charts more pretty
//case is important to not cause naming conflicts within QMK source
    // modifiers
#define XXXX                KC_NO
#define Lctl                KC_LCTL
#define Rctl                KC_RCTL
#define Lgui                KC_LGUI
#define Rgui                KC_RGUI
#define Lalt                KC_LALT
#define Ralt                KC_RALT
    // keys
#define comma               KC_COMM
#define dot                 KC_DOT
#define slash               KC_SLSH


// Tap Dance declarations
#define TD_NAV              0
#define TD_ALT_NAV          1

// Layers
#define _BASE               0
#define _NUM                1

// Layer keys
#define L_NUM               MO(_NUM)

#define L_SLASH             LT(_NUM, KC_SLSH)

//custom macros
#define C_SPAC              LCTL_T(KC_SPC)
#define C_BSPC              LSFT_T(KC_BSPC)
#define MOD_P               MT(MOD_LCTL | MOD_LGUI, KC_P)

#define C_CMETA             LGUI(KC_LCTL)

#define C_STAB              LSFT(KC_TAB)

//KC_GRV KC_EXLM KC_AT KC_HASH KC_DLR KC_PERC KC_CIRC KC_AMPR KC_ASTR
// KC_LPRN KC_RPRN
// KC_LCBR KC_RCBR
// KC_LBRC KC_RBRC
// KC_MINS KC_UNDS KC_BACKSLASH KC_EQL KC_PLUS
//KC_F11  KC_F12

//` ~ ! @ # $ % ^ & * ( ) - _ = + [ ] { } \ | ; : ' " , < . > / ?

// Layout Aliases
#define LAYOUT_voyager_wrapper(...) LAYOUT(__VA_ARGS__)

#define LAYOUT_willy_wrapper(...) LAYOUT(__VA_ARGS__)

#define LAYOUT_oxymoron_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_orthomoron_wrapper(...) LAYOUT(__VA_ARGS__)

#define LAYOUT_mini36_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

#define LAYOUT_planck_wrapper(...) LAYOUT_planck_2x2u(__VA_ARGS__)

#define NEW \
/* ┌──────┬──────┬──────┬──────┬──────┐             ┌──────┬──────┬──────┬──────┬──────┐ */ \
    KC_1  ,KC_2  ,KC_3  , KC_4 ,KC_5  ,              KC_6  ,KC_7  ,KC_8  , KC_9 ,KC_0  ,    \
/* ├──────┼──────┼──────┼──────┼──────┤             ├──────┼──────┼──────┼──────┼──────┤ */ \
    KC_Q  ,KC_W  ,KC_E  , KC_R ,KC_T  ,              KC_Y  ,KC_U  ,KC_I  ,KC_O  ,KC_P  ,    \
/* ├──────┼──────┼──────┼──────┼──────┤             ├──────┼──────┼──────┼──────┼──────┤ */ \
    KC_A  ,KC_S  ,KC_D  ,KC_F  ,KC_G  ,              KC_H  ,KC_J  ,KC_K  ,KC_L  ,KC_SCLN,   \
/* ├──────┼──────┼──────┼──────┼──────┤             ├──────┼──────┼──────┼──────┼──────┤ */ \
    KC_Z  ,KC_X  ,KC_C  ,KC_V  ,KC_B  ,              KC_N  ,KC_M  ,comma ,dot   ,slash ,    \
/* └──────┴──────┴──────┴──────┼──────┤             ├──────┼──────┴──────┴──────┴──────┘ */ \
                                TD(TD_NAV),          L_NUM ,                                \
/*                             └─┬────┴─┐         ┌─┴────┬─┘                             */ \
                                  C_SPAC,          C_BSPC,                                  \
/*                               └──────┘         └──────┘                               */ \

#define BASE \
/* ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐ */ \
      KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  , MOD_P  ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
      KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
      KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,  KC_N  ,  KC_M  ,KC_COMM , KC_DOT ,L_SLASH ,    \
/* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤ */ \
                      TD(TD_NAV) , KC_LSFT, C_SPAC ,C_BSPC, KC_NO  ,L_NUM                          \
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
/*                └────┴────┴────┴────┴────┴────┘      */ \
) \
/* ┌───────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───┬───────┐ */ \
    KC_ESC ,l01 ,l02 ,l03 ,l04 ,l05 ,r01 ,r02 ,r03 ,r04 ,r05,KC_BSPC,    \
/* ├───────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬──┴┐      | */ \
    KC_TAB  ,l06 ,l07 ,l08 ,l09 ,l10 ,r06 ,r07 ,r08 ,r09 ,r10, XXXX ,    \
/* ├──────┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬┴──────┤ */ \
    L_NUM ,l11 ,l12 ,l13 ,l14 ,l15, r11 ,r12 ,r13 ,r14 ,r15 ,KC_RSFT,    \
/* ├──────┴┬───┴───┬┴────┴────┴────┴────┴────┴────┴─┬──┴────┴┬──────┤ */ \
    KC_LCTL,KC_LGUI,XXXX, XXXX, MOD_SPC, XXXX       ,L_NAV,XXXX,C_CMETA  \
/* └───────┴───────┴────────────────────────────────┴────────┴──────┘  */

// Convert 3x10_6 unibody to oxymoron ortholinear
#define CONV_ORTHOMORON(k) K36_TO_ORTHOMORON(k)
#define K36_TO_ORTHOMORON( \
/* ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐ */ \
    l01 ,l02 ,l03 ,l04 ,l05 ,r01 ,r02 ,r03 ,r04 ,r05 ,    \
/* ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤ */ \
    l06 ,l07 ,l08 ,l09 ,l10 ,r06 ,r07 ,r08 ,r09 ,r10 ,    \
/* ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤ */ \
    l11 ,l12 ,l13 ,l14 ,l15, r11 ,r12 ,r13 ,r14 ,r15 ,    \
/* └────┴────┴────┼────┼────┼────┼────┼────┼────┼────┤ */ \
                   l16 ,l17 ,l18 ,r16 ,r17 , r18          \
/*                └────┴────┴────┴────┴────┴────┘      */ \
) \
/* ┌───────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬───────┐ */ \
    KC_ESC ,l01 ,l02 ,l03 ,l04 ,l05 ,r01 ,r02 ,r03 ,r04 ,r05 ,KC_BSPC,    \
/* ├───────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼───────┤ */ \
    KC_TAB ,l06 ,l07 ,l08 ,l09 ,l10 ,r06 ,r07 ,r08 ,r09 ,r10 ,KC_ENT ,    \
/* ├───────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼───────┤ */ \
    KC_LSFT,l11 ,l12 ,l13 ,l14 ,l15, r11 ,r12 ,r13 ,r14 ,r15 ,KC_RSFT,    \
/* ├────┬──┴─┬──┴─┬──┴─┬──┴────┴────┴────┴────┴────┴────┴────┴───────┤ */ \
    Lctl,Lgui,Lalt,XXXX, XXXX,l18,L_NAV, XXXX,r16,L_NUM,Ralt,Rgui,Rctl
/* └────┴────┴────┴────┴──────────┴────┴─────────┴────┴────┴────┴────┘  */


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
/*                └────┴────┴────┴────┴────┴────┘      */ \
)\
/* ┌────┬────┬────┬────┬────┐                ┌────┬────┬────┬────┬────┐ */ \
    l01 ,l02 ,l03 ,l04 ,l05 ,                 r01 ,r02 ,r03 ,r04 ,r05 ,    \
/* ├────┼────┼────┼────┼────┤                ├────┼────┼────┼────┼────┤ */ \
    l06 ,l07 ,l08 ,l09 ,l10 ,                 r06 ,r07 ,r08 ,r09 ,r10 ,    \
/* ├────┼────┼────┼────┼────┤                ├────┼────┼────┼────┼────┤ */ \
    l11 ,l12 ,l13 ,l14 ,l15,                  r11 ,r12 ,r13 ,r14 ,r15 ,    \
/* └────┴────┴────┼────┼────┼────┐      ┌────┼────┴────┼────┴────┴────┘ */ \
                   l16 ,l17 ,l18 ,       r16 ,r17 , r18                    \
/*                └────┴────┴────┘      └────┴────┴────┘                */ \

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
/*                └────┴────┴────┴────┴────┴────┘      */ \
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


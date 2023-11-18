#include QMK_KEYBOARD_H

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
        // case _GAME:
        //     oled_write_P(PSTR("BASE-GAMING\n"), false);
        //     break;
        case _NAV:
            oled_write_P(PSTR("NAVIGATION\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("NUMBERS\n"), false);
            break;
        // case _ADJ:
        //     oled_write_P(PSTR("SETTINGS\n"), false);
        //     break;
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

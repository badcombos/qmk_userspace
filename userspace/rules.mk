
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

KEY_OVERRIDE_ENABLE = yes
TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
LEADER_ENABLE = yes
CAPS_WORD_ENABLE = yes
# UNICODEMAP_ENABLE = yes

COMBO_ENABLE = yes
INTROSPECTION_KEYMAP_C = badcombos.c

SRC += features/casemodes.c
SRC += features/oled.c
# SRC += features/tapdance.c

ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), planck/rev6_drop))
	OPT_DEFS += -DIS_PLANCK
endif

ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), controllerworks/mini36))
	OPT_DEFS += -DIS_MINI36
endif

ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), rainkeebs/oxymoron))
	OPT_DEFS += -DIS_OXYMORON
	ENCODER_ENABLE = yes #required even if no encorder is installed
endif

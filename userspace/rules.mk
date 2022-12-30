SRC += badcombos.c

KEY_OVERRIDE_ENABLE = yes
AUTO_SHIFT_ENABLE = no
TAP_DANCE_ENABLE = yes

COMBO_ENABLE = yes
VPATH += keyboards/gboards

CONSOLE_ENABLE = no

BOOTMAGIC_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), planck/rev6_drop))
	OPT_DEFS += -DIS_PLANCK
endif

ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), controllerworks/mini36))
	OPT_DEFS += -DIS_MINI36
endif
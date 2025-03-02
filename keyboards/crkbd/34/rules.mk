CONVERT_TO = rp2040_ce

CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
LAYER_LOCK_ENABLE = yes

SRC += features/custom_shift_keys.c
SRC += features/swapper.c

# optimisations
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

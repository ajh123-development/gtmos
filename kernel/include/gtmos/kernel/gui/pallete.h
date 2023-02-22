#ifndef _GUI_PALLETE_H
#define _GUI_PALLETE_H

#include <stdint.h>
#include <string.h>

enum GuiColor {
	DEFAULT_DESKTOP = 0xc0c7c8,
    WINDOW_FILL = 0xFFFFFF,
    WINDOW_BORDER_ACTIVE = 0x0000a8,
    WINDOW_BORDER_INACTIVE = 0xc0c7c8,
    WINDOW_BORDER_TITLE_ACTIVE = 0x0000a8,
    WINDOW_BORDER_TITLE_INACTIVE = 0xFFFFFF,
    WINDOW_BORDER_OUTLINE = 0x000000,
    WINDOW_BORDER_TITLE_TEXT_INACTIVE = 0xFFFFFF,
    WINDOW_BORDER_TITLE_TEXT_ACTIVE = 0x000000,
};

#endif /* _GUI_PALLETE_H */

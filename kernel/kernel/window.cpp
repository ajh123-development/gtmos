#include <gtmos/kernel/gui/objects.h>
#include <gtmos/kernel/device/framebuffer.h>
#include <gtmos/kernel/device/tty.h>
#include <gtmos/kernel/gui/pallete.h>
#include <gtmos/logging.h>

Window WindowCreate(int x, int y, int width, int height, const char *title) {
    Window window;
    window.winX = x;
    window.winY = y;
    window.winW = width;
    window.winH = height;
    window.title = title;
    window.active = 1;
    return window;
}

void WindowDraw(Window window) {
    if (window.active == 1) {
        Buffer_FillRect(WINDOW_BORDER_OUTLINE, window.winX-4, window.winY-4, window.winW+8, window.winH+8);
        Buffer_FillRect(WINDOW_BORDER, window.winX-3, window.winY-3, window.winW+6, window.winH+6);
        Buffer_FillRect(WINDOW_BORDER_OUTLINE, window.winX-1, window.winY-1, window.winW+2, window.winH+2);
        Buffer_FillRect(WINDOW_FILL, window.winX, window.winY, window.winW, window.winH);
        Buffer_FillRect(WINDOW_TITLE_ACTIVE, window.winX, window.winY, window.winW, 18);
        Buffer_FillRect(WINDOW_BORDER_OUTLINE, window.winX-4, window.winY+18, window.winW+8, 1);
        Buffer_SetTextColor(WINDOW_TITLE_TEXT_ACTIVE);
    }
    if (window.active == 0) {
        Buffer_FillRect(WINDOW_BORDER_OUTLINE, window.winX-4, window.winY-4, window.winW+8, window.winH+8);
        Buffer_FillRect(WINDOW_BORDER, window.winX-3, window.winY-3, window.winW+6, window.winH+6);
        Buffer_FillRect(WINDOW_BORDER_OUTLINE, window.winX-1, window.winY-1, window.winW+2, window.winH+2);
        Buffer_FillRect(WINDOW_FILL, window.winX, window.winY, window.winW, window.winH);
        Buffer_FillRect(WINDOW_TITLE_INACTIVE, window.winX, window.winY, window.winW, 18);
        Buffer_FillRect(WINDOW_BORDER_OUTLINE, window.winX-4, window.winY+18, window.winW+8, 1);
        Buffer_SetTextColor(WINDOW_TITLE_TEXT_INACTIVE);
    }
    size_t length = strlen(window.title) * 8;
    int x = ((window.winW / 2) - (length / 2)) + window.winX;
    Term_Setpos(x, window.winY+5);
    Term_WriteString(window.title);
}
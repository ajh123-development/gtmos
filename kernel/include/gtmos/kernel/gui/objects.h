#ifndef _GUI_OBJECTS_H
#define _GUI_OBJECTS_H

struct Window {
	int winX;
	int winY;
	int winW;
	int winH;
    const char* title;
	int active;
};

Window WindowCreate(int x, int y, int width, int height, const char *title);
void WindowDraw(Window window);

#endif /* _GUI_OBJECTS_H */

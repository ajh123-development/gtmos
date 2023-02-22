#include <gtmos/kernel/device/framebuffer.h>
#include <gtmos/kernel/device/tty.h>
#include <gtmos/logging.h>
#include <gtmos/limine.h>

#include "font.h"
#include "vga.h"

static volatile struct limine_framebuffer_request buffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};
struct limine_framebuffer *buffer;

int ok = 0;
int posX = 0;
int posY = 0;
uint32_t textColor = VGA_COLOR_BLACK;

void Buffer_Initialize() {
    if (buffer_request.response->framebuffer_count > 0) {
        buffer = buffer_request.response->framebuffers[0];
        ok = 1;
        log_debug("FrameBuffer", "A framebuffer was found!");
    } else {
        log_warn("FrameBuffer", "No framebuffers found!");
    }
}

void Buffer_PlotPixel(int x,int y, uint32_t color) {
    if (ok) {
        size_t fb_index = y * (buffer->pitch / sizeof(uint32_t)) + x;
        uint32_t *fb = (uint32_t *)buffer->address;

        fb[fb_index] = color;
    }
}

void Buffer_FillColor(uint32_t color) {
    if (ok) {
        for (int y = 0; y < buffer->height; y++)
        {
            for (int x = 0; x < buffer->width; x++)
                Buffer_PlotPixel(x, y, color);
        }
    }
}

void Buffer_SetTextColor(uint32_t color) {
    textColor = color;
}

// making use of bresenham's line algorithm
void Buffer_PlotLine(int x_start_pos, int y_start_pos, int x_end_pos, int y_end_pos, uint32_t color) {
    if (ok) {
        int dx;
        int dy;
        int sx;
        int sy;
        int error1;
        int error2;

        if (x_start_pos == x_end_pos)
        {
            if (y_start_pos < y_end_pos)
                for (int y = y_start_pos; y <= y_end_pos; y++)
                    Buffer_PlotPixel(x_start_pos, y, color);
            else
                for (int y = y_end_pos; y <= y_start_pos; y++)
                    Buffer_PlotPixel(x_start_pos, y, color);

            return;
        }

        if (y_start_pos == y_end_pos)
        {
            if (x_start_pos < x_end_pos)
                for (int x = x_start_pos; x <= x_end_pos; x++)
                    Buffer_PlotPixel(x, y_start_pos, color);
            else
                for (int x = x_end_pos; x <= x_start_pos; x++)
                    Buffer_PlotPixel(x, y_start_pos, color);

            return;
        }

        if (x_start_pos < x_end_pos)
        {
            dx = x_end_pos - x_start_pos;
            sx = 1;
        }
        else
        {
            dx = x_start_pos - x_end_pos;
            sx = -1;
        }

        if (y_start_pos < y_end_pos)
        {
            dy = -(y_end_pos - y_start_pos);
            sy = 1;
        }
        else
        {
            dy = -(y_start_pos - y_end_pos);
            sy = -1;
        }

        error1 = dx + dy;

        Buffer_PlotPixel(x_start_pos, y_start_pos, color);

        while (x_start_pos != x_end_pos && y_start_pos != y_end_pos)
        {
            error2 = 2 * error1;

            if (error2 >= dy)
            {
                error1 += dy;
                x_start_pos += sx;
            }

            if (error2 <= dx)
            {
                error1 += dx;
                y_start_pos += sy;
            }

            Buffer_PlotPixel(x_start_pos, y_start_pos, color);
        }
    }
}

void Term_Initialize() {
    Buffer_Initialize();
    Buffer_FillColor(VGA_COLOR_WHITE);
}

void Term_Setpos(int x, int y) {
    posX = x;
    posY = y;
}

void Term_Putchar(char c) {
    for (int row = 0; row < 8; row++) {
        int data = font8x8_basic[c][row];
        for (int col = 0; col < 8; col++) {
            if ((data >> col) & 1) {
                if ((col+(posX*8)) > buffer->width) {
                    posX = 0;
                    posY = posY + 1;
                }
                Buffer_PlotPixel(col+(posX*8), row+(posY*8), textColor);
            }
        }
    }

}

void Term_Write(const char* data, size_t size) {
    for (int i = 0; i < size; i++) {
        char c = data[i];
        if (c == '\n') {
            posX = 0;
            posY = posY + 1;
        } else {
            Term_Putchar(c);
            posX = posX + 1;
        }
    }
}

void Term_WriteString(const char* data) {
    Term_Write(data, sizeof(data));
}
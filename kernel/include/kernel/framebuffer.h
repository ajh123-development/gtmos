#ifndef ARCH_FRAMEBUFFER_H
#define ARCH_FRAMEBUFFER_H

#include <stdint.h>

void Buffer_Initialize();
void Buffer_FillColor(uint32_t color);
void Buffer_SetTextColor(uint32_t color);
void Buffer_PlotPixel(int x,int y, uint32_t color);
void Buffer_PlotLine(int x_start_pos, int y_start_pos, int x_end_pos, int y_end_pos, uint32_t color);

#endif /* ARCH_FRAMEBUFFER_H */

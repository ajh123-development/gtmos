#ifndef _KERNEL_FRAMEBUFFER_H
#define _KERNEL_FRAMEBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void Buffer_Initialize();
void Buffer_FillColor(uint32_t color);
void Buffer_SetTextColor(uint32_t color);
void Buffer_PlotPixel(int x,int y, uint32_t color);
void Buffer_PlotLine(int x_start_pos, int y_start_pos, int x_end_pos, int y_end_pos, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_FRAMEBUFFER_H */

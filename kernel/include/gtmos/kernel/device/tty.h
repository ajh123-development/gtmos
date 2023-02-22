#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gtmos/kernel/arch/io.h>
#include <stddef.h>

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/** Term_Initialize:
 *  Initializes the terminal by clearing the screen.
 */
void Term_Initialize();

/** Term_Putchar:
 *  Puts a character at the current terminal position.
 * 
 *  @param c The character to display
 */
void Term_Putchar(char c);

/** Term_Write:
 *  Puts a character buffer (a string) at the current 
 *  terminal position until a certain 'size' has been 
 *  reached.
 * 
 *  @param data The character buffer to display
 *  @param size The amount of character you want to use 
 *              from the buffer
 */
void Term_Write(const char* data, size_t size);

/** Term_WriteString:
 *  Puts a character buffer (a string) at the current 
 *  terminal position.
 * 
 *  @param data The character buffer to display
 */
void Term_WriteString(const char* data);

/** Term_Setpos:
 *  Moves the current terminal position to a new one.
 * 
 *  @param x The x coordinate
 *  @param y The y coordinate
 */
void Term_Setpos(int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* _KERNEL_TTY_H */

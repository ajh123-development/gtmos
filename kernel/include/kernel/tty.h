#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <kernel/io.h>
#include <stddef.h>

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/** terminal_initialize:
 *  Initializes the terminal by clearing the screen.
 */
void terminal_initialize(void);

/** terminal_putchar:
 *  Puts a character at the current terminal position.
 * 
 *  @param c The character to display
 */
void terminal_putchar(char c);

/** terminal_write:
 *  Puts a character buffer (a string) at the current 
 *  terminal position until a certain 'size' has been 
 *  reached.
 * 
 *  @param data The character buffer to display
 *  @param size The amount of character you want to use 
 *              from the buffer
 */
void terminal_write(const char* data, size_t size);

/** terminal_writestring:
 *  Puts a character buffer (a string) at the current 
 *  terminal position.
 * 
 *  @param data The character buffer to display
 */
void terminal_writestring(const char* data);

/** terminal_movecursor:
 *  Moves the cursor of the framebuffer to the given 
 *  position. Note this dose not move where the 
 *  terminal's cursor for writing is.
 *
 *  @param pos The new position of the cursor
 */
void terminal_movecursor(unsigned short pos);

#endif /* _KERNEL_TTY_H */

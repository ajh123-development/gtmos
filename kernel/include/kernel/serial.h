#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

#include <kernel/io.h>
#include <stddef.h>

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

/** serial_initialize:
 *  Initializes the serial connection at a given port.
 * 
 * @param com The com port to communicate on
 */
void serial_initialize(unsigned short com);

/** serial_putchar:
 *  Puts a character at the current serial position.
 * 
 *  @param com The com port to communicate on
 *  @param c   The character to display
 */
void serial_putchar(unsigned short com, char c);

/** serial_write:
 *  Puts a character buffer (a string) at the current 
 *  serial position until a certain 'size' has been 
 *  reached.
 *
 *  @param com  The com port to communicate on
 *  @param data The character buffer to display
 *  @param size The ammount of character you want to use 
 *              from the buffer
 */
void serial_write(unsigned short com, const char* data, size_t size);

/** serial_writestring:
 *  Puts a character buffer (a string) at the current 
 *  position.
 *
 *  @param com  The com port to communicate on
 *  @param data The character buffer to display
 */
void serial_writestring(unsigned short com, const char* data);

#endif /* _KERNEL_SERIAL_H */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

void lcdWriteChar(char *str);
void lcdInit(void);
void lcdWriteNibble(uint8_t nibble, uint8_t isChar);
void lcdWriteByte(uint8_t byte, uint8_t isChar);

#endif

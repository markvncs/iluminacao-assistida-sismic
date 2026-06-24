#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void i2cInit(void);
uint8_t i2cSendByte(uint8_t addr, uint8_t data);

#endif

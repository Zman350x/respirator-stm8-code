#ifndef __I2C_H__
#define __I2C_H__

#include "stm8.h"

#define I2C_BUFFERSIZE  10

extern uint8_t txBuffer[I2C_BUFFERSIZE];
extern volatile uint8_t rxBuffer[I2C_BUFFERSIZE];

void i2cSendAddress(uint8_t address, I2C_Direction_TypeDef direction);
I2C_Event_TypeDef i2cGetLastEvent(void);

void i2cTransmit(uint8_t address, uint8_t numberOfBytes);
void i2cReveive(uint8_t address, uint8_t numberOfBytes);

#endif

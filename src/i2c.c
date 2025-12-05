#include "stm8.h"
#include "i2c.h"

extern I2C_Direction_TypeDef i2cDirection;
extern uint8_t i2cAddress;
extern volatile uint8_t i2cNumberOfBytes;

void i2cSendAddress(uint8_t address, I2C_Direction_TypeDef direction)
{
    address &= (uint8_t)0xFE;
    I2C->DR = (uint8_t)(address | (uint8_t)direction);
}

I2C_Event_TypeDef i2cGetLastEvent(void)
{
    if (I2C->SR2 & I2C_SR2_AF)
        return I2C_EVENT_SLAVE_ACK_FAILURE;

    // Read the I2C status registers
    uint16_t flag1 = I2C->SR1;
    uint16_t flag2 = I2C->SR3;

    // Get the last event value from I2C status register
    return (I2C_Event_TypeDef) ((uint16_t)((uint16_t)flag2 << 8) | (uint16_t)flag1);
}

// Transmits the first `numberOfBytes` bytes from the TX buffer
void i2cTransmit(uint8_t address, uint8_t numberOfBytes)
{
    if (numberOfBytes > I2C_BUFFERSIZE)
        return;

    i2cDirection = I2C_DIRECTION_TX;
    i2cAddress = address;
    i2cNumberOfBytes = numberOfBytes;

    I2C->CR2 |= I2C_CR2_START;
}

// Receives the first `numberOfBytes` bytes into the RX buffer
void i2cReveive(uint8_t address, uint8_t numberOfBytes)
{
    if (numberOfBytes > I2C_BUFFERSIZE)
        return;

    i2cDirection = I2C_DIRECTION_RX;
    i2cAddress = address;
    i2cNumberOfBytes = numberOfBytes;

    I2C->CR2 |= I2C_CR2_START;
}

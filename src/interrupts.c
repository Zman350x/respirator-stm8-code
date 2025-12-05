#include "clangd_sdcc_compat.h"
#include "stm8.h"
#include "interrupts.h"
#include "i2c.h"

volatile uint32_t counter4ms;
volatile bool buttonStatus;
volatile uint32_t lastValidButtonInterrupt;

I2C_Direction_TypeDef i2cDirection;
uint8_t i2cAddress;
uint8_t txBuffer[I2C_BUFFERSIZE];
volatile uint8_t rxBuffer[I2C_BUFFERSIZE];
volatile uint8_t i2cNumberOfBytes;

static volatile uint8_t i2cIndex;

// INTERRUPTS

void EXTI0_ISR(void) __interrupt(EXTI0_IRQn)
{
    // Start software debouncing
    if (lastValidButtonInterrupt == 0)
        lastValidButtonInterrupt = counter4ms;
}

void I2C_ISR(void) __interrupt(I2C_IRQn)
{
    switch (i2cGetLastEvent())
    {
        case I2C_EVENT_MASTER_MODE_SELECT:
            i2cSendAddress(i2cAddress, i2cDirection);
            i2cIndex = 0;
            I2C->CR2 |= I2C_CR2_ACK; // Respond with ACKs
            break;

        case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:
            if (i2cNumberOfBytes == 0)
                break; // Otherwise fall through

        case I2C_EVENT_MASTER_BYTE_TRANSMITTING:
            I2C->DR = txBuffer[i2cIndex++];
            --i2cNumberOfBytes;
            break;

        case I2C_EVENT_MASTER_BYTE_TRANSMITTED:
            I2C->CR2 |= I2C_CR2_STOP;
            break;

        case I2C_EVENT_MASTER_BYTE_RECEIVED:
            if (i2cNumberOfBytes == 1)
            {
                I2C->CR2 &= ~I2C_CR2_ACK; // Respond with NACK
                I2C->CR2 |= I2C_CR2_STOP;
            }
            rxBuffer[i2cIndex++] = I2C->DR;
            --i2cNumberOfBytes;
            break;

        default:
            break;
    }
}

void TIM4_ISR(void) __interrupt(TIM4_IRQn)
{
    // Software debouncing
    if (lastValidButtonInterrupt && lastValidButtonInterrupt + 10 < counter4ms)
    {
        buttonStatus = !(GPIOA->IDR & GPIO_PIN_3); // Button active low
        lastValidButtonInterrupt = 0;
    }

    ++counter4ms; // Every 4 ms
    TIM4->SR = 0; // Reset interrupt
}

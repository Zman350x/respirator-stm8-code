#include "stm8.h"
#include "setup.h"

void gpioSetup(void)
{
    // Button
    GPIOA->CR2 |= GPIO_PIN_3; // Enable interrupts on button
    ITC_EXTI->CR1 = (0b11 << 0); // Port A interrupts on rising and falling edge

    // LEDs and Buzzer
    GPIOD->ODR = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; // Turn off LEDs as they're active low
    GPIOD->DDR = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; // Configure buzzer and LEDs as outputs
    GPIOD->CR1 = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; // Push-pull outputs

    // Fans and ERM
    GPIOC->DDR = GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7; // Configure fans and ERM motor as outputs
    GPIOC->CR1 = GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7; // Push-pull outputs
}

void timerSetup(void)
{
    TIM4->PSCR = 5; // Prescaler of 32, results in a 62.5kHz timer
    TIM4->ARR = 249; // (249 + 1)/(62.5kHz) means interrupt every 4 ms
    TIM4->CR1 = 0x01; // Enable timer 4
    TIM4->IER = 0x01; // Enbale timer 4 interrupts
}

void i2cSetup(void)
{
    I2C->CR1 = 0; // Disable I2C for setup

    I2C->FREQR = 2; // 2MHz (must be system peripheral clock value)
    I2C->CCRL = 10; // (10 * (2MHz)^-1 * 2)^-1 = 100kHz
    I2C->TRISER = 3; // (system peripheral clock value in MHz + 1)

    I2C->CR1 = 1; // Enable I2C

    I2C->OARH = I2C_OARH_ADDCONF; // Configure 7-bit addressing

    /* I2C->ITR |= I2C_ITR_ITBUFEN | I2C_ITR_ITEVTEN; // Enable interrupts */
}

// Assumes all registers to be in their default/reset state
void setup(void)
{
    __asm__("sim"); // Disable interrupt support for setup

    gpioSetup();
    timerSetup();
    i2cSetup();

    __asm__("rim"); // Enable interrupt support
}

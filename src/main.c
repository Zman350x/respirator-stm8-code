#include "stm8.h"
#include "setup.h"
#include "interrupts.h"
#include "i2c.h"

/* PINOUT
 *
 * PA3 - BUTTON
 *
 * PB4 - SCL
 * PB5 - SDA
 *
 * PC3 - ERM MOTOR
 * PC4 - FAN 2 TACHO
 * PC5 - FAN 2
 * PC6 - FAN 1 TACHO
 * PC7 - FAN 1
 *
 * PD1 - SWIM
 * PD2 - BUZZER
 * PD3 - LED BLUE
 * PD4 - LED GREEN
 * PD5 - LED RED
 * PD6 - BATTERY LEVEL
 *
 */

// FUNCTION PROTOTYPES

void reset(void);

// MAIN

int main(void) // Clock at 2MHz at startup
{
    setup();
    reset();

    /* txBuffer[0] = 0x36; */
    /* txBuffer[1] = 0x82; */
    /* i2cTransmit(0x59, 2); */
    /* i2cReveive(0x59, 9); */

    while (1)
    {
        /* buttonStatus = !(GPIOA->IDR & GPIO_PIN_3); // Button active low */
        if (buttonStatus)
        {
            /* GPIOD->ODR &= ~(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5); */
            GPIOC->ODR |= /* GPIO_PIN_3 | */ GPIO_PIN_5 | GPIO_PIN_7;
            /* GPIOD->ODR |= GPIO_PIN_2; */
        }
        else
        {
            /* GPIOD->ODR |= GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; */
            GPIOC->ODR &= ~(/* GPIO_PIN_3 | */ GPIO_PIN_5 | GPIO_PIN_7);
            /* GPIOD->ODR &= ~GPIO_PIN_2; */
        }
    }
}

// HELPER FUNCTIONS

void reset(void)
{
    counter4ms = 0;
    lastValidButtonInterrupt = 0;
    buttonStatus = !(GPIOA->IDR & GPIO_PIN_3); // Button active low
}

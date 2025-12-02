#include "clangd_sdcc_compat.h"
#include "stm8.h"
#include <stdint.h>

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

void setup(void);

// GLOBALS

uint32_t counter4ms;

uint32_t lastValidButtonInterrupt;
bool buttonStatus;

// MAIN

int main(void) // Clock at 2MHz at startup
{
    __asm__("rim"); // Enable interrupt support

    setup();

    while (1)
    {
        buttonStatus = !(GPIOA->IDR & GPIO_PIN_3); // Button active low
        /* if (counter4ms > 500) */
        if (buttonStatus)
        {
            GPIOD->ODR &= ~(GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
            GPIOC->ODR |= GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7;
            GPIOD->ODR |= GPIO_PIN_2;
            /* counter4ms = 0; */
        }
        else
        {
            GPIOD->ODR |= GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
            GPIOC->ODR &= ~(GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7);
            GPIOD->ODR &= ~GPIO_PIN_2;
        }
    }
}

// HELPER FUNCTIONS

void setup(void)
{
    /* GPIOA->CR2 |= GPIO_PIN_3; // Enable interrupts on button */
    ITC_EXTI->CR1 = (0b11 << 0); // Port A interrupts on rising and falling edge
    buttonStatus = !(GPIOA->IDR & GPIO_PIN_3); // Button active low
    lastValidButtonInterrupt = 0;

    TIM4->PSCR = 5; // Prescaler of 32, results in a 62.5kHz timer
    TIM4->ARR = 249; // (249 + 1)/(62.5kHz) means interrupt every 4 ms
    TIM4->CR1 = 0x01; // Enable timer 4
    /* TIM4->IER = 0x01; // Enbale timer 4 interrupts */
    counter4ms = 0;

    GPIOD->ODR = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; // Turn off LEDs as they're active low
    GPIOD->DDR = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; // Configure buzzer and LEDs as outputs
    GPIOD->CR1 = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; // Push-pull outputs

    GPIOC->DDR = GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7; // Configure fans and ERM motor as outputs
    GPIOC->CR1 = GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7; // Push-pull outputs
}

// INTERRUPTS

void EXTI0_ISR(void) __interrupt(EXTI0_IRQn)
{
    if (lastValidButtonInterrupt + 10 < counter4ms)
        buttonStatus = !buttonStatus;
}

void TIM4_ISR(void) __interrupt(TIM4_IRQn)
{
    ++counter4ms; // Every 4 ms
    TIM4->SR = 0; // Reset interrupt
}

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include "clangd_sdcc_compat.h"
#include "stm8.h"

extern volatile uint32_t counter4ms;
extern volatile bool buttonStatus;
extern volatile uint32_t lastValidButtonInterrupt;

void EXTI0_ISR(void) __interrupt(EXTI0_IRQn);
void I2C_ISR(void) __interrupt(I2C_IRQn);
void TIM4_ISR(void) __interrupt(TIM4_IRQn);

#endif

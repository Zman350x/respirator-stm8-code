#ifndef __PINS_H__
#define __PINS_H__

#include <stdint.h>

// GPIO

typedef struct
{
    uint8_t ODR;
    uint8_t IDR;
    uint8_t DDR;
    uint8_t CR1;
    uint8_t CR2;
} GPIO_TypeDef;

#define GPIOA               ((volatile GPIO_TypeDef *) 0x5000)
#define GPIOB               ((volatile GPIO_TypeDef *) 0x5005)
#define GPIOC               ((volatile GPIO_TypeDef *) 0x500A)
#define GPIOD               ((volatile GPIO_TypeDef *) 0x500F)
#define GPIOE               ((volatile GPIO_TypeDef *) 0x5014)
#define GPIOF               ((volatile GPIO_TypeDef *) 0x5019)

#define GPIO_PIN_0          ((uint8_t) 0x01U)
#define GPIO_PIN_1          ((uint8_t) 0x02U)
#define GPIO_PIN_2          ((uint8_t) 0x04U)
#define GPIO_PIN_3          ((uint8_t) 0x08U)
#define GPIO_PIN_4          ((uint8_t) 0x10U)
#define GPIO_PIN_5          ((uint8_t) 0x20U)
#define GPIO_PIN_6          ((uint8_t) 0x40U)
#define GPIO_PIN_7          ((uint8_t) 0x80U)

// INTERRUPTS

typedef struct
{
    uint8_t CR1;
    uint8_t CR2;
} ITC_EXTI_TypeDef;

typedef struct
{
    uint8_t SPR1;
    uint8_t SPR2;
    uint8_t SPR3;
    uint8_t SPR4;
    uint8_t SPR5;
    uint8_t SPR6;
    uint8_t SPR7;
    uint8_t SPR8;
} ITC_SPR_TypeDef;

#define ITC_EXTI            ((volatile ITC_EXTI_TypeDef *) 0x50A0)
#define ITC_SPR             ((volatile ITC_SPR_TypeDef *) 0x7F70)

#define TLI_IRQn            0
#define AWU_IRQn            1
#define CLK_IRQn            2
#define EXTI0_IRQn          3
#define EXTI1_IRQn          4
#define EXTI2_IRQn          5
#define EXTI3_IRQn          6
#define EXTI4_IRQn          7
#define SPI_IRQn            10
#define TIM1_IRQn           11
#define TIM1_CC_IRQn        12
#define TIM2_IRQn           13
#define TIM2_CC_IRQn        14
#define UART1_TX_CMPLT_IRQn 17
#define UART1_FULL_IRQn     18
#define I2C_IRQn            19
#define ADC1_IRQn           22
#define TIM4_IRQn           23
#define FLASH_IRQn          24

// TIMERS

typedef struct
{
    uint8_t CR1;
    uint16_t _reserved;
    uint8_t IER;
    uint8_t SR;
    uint8_t EGR;
    uint8_t CNTR;
    uint8_t PSCR;
    uint8_t ARR;
} BASIC_TIMER_TypeDef;

#define TIM4                ((volatile BASIC_TIMER_TypeDef *) 0x5340)

#endif

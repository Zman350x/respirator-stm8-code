#ifndef __STM8_H__
#define __STM8_H__

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

// I2C

typedef struct
{
    uint8_t CR1;
    uint8_t CR2;
    uint8_t FREQR;
    uint8_t OARL;
    uint8_t OARH;
    uint8_t _reserved;
    uint8_t DR;
    uint8_t SR1;
    uint8_t SR2;
    uint8_t SR3;
    uint8_t ITR;
    uint8_t CCRL;
    uint8_t CCRH;
    uint8_t TRISER;
    uint8_t PECR;
} I2C_TypeDef;

#define I2C                 ((volatile I2C_TypeDef *) 0x5210)

#define I2C_CR2_ACK         4
#define I2C_CR2_STOP        2
#define I2C_CR2_START       1
#define I2C_SR2_AF          4
#define I2C_OARH_ADDCONF    64
#define I2C_ITR_ITBUFEN     4
#define I2C_ITR_ITEVTEN     2

typedef enum : uint8_t
{
    I2C_DIRECTION_TX = (uint8_t)0x00,  /*!< Transmission direction */
    I2C_DIRECTION_RX = (uint8_t)0x01   /*!< Reception direction */
} I2C_Direction_TypeDef;

typedef enum : uint16_t
{
    I2C_EVENT_MASTER_MODE_SELECT                = (uint16_t)0x0301,  /*!< BUSY, MSL and SB flag */
    I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED  = (uint16_t)0x0782,  /*!< BUSY, MSL, ADDR, TXE and TRA flags */
    I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED     = (uint16_t)0x0302,  /*!< BUSY, MSL and ADDR flags */
    I2C_EVENT_MASTER_MODE_ADDRESS10             = (uint16_t)0x0308,  /*!< BUSY, MSL and ADD10 flags */
    I2C_EVENT_MASTER_BYTE_RECEIVED              = (uint16_t)0x0340,  /*!< BUSY, MSL and RXNE flags */
    I2C_EVENT_MASTER_BYTE_TRANSMITTING          = (uint16_t)0x0780,  /*!< TRA, BUSY, MSL, TXE flags */
    I2C_EVENT_MASTER_BYTE_TRANSMITTED           = (uint16_t)0x0784,  /*!< EV8_2: TRA, BUSY, MSL, TXE and BTF flags */
    I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED    = (uint16_t)0x0202,  /*!< BUSY and ADDR flags */
    I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED = (uint16_t)0x0682,  /*!< TRA, BUSY, TXE and ADDR flags */
    I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED  = (uint16_t)0x1200,  /*!< EV2: GENCALL and BUSY flags */
    I2C_EVENT_SLAVE_BYTE_RECEIVED               = (uint16_t)0x0240,  /*!< BUSY and RXNE flags */
    I2C_EVENT_SLAVE_STOP_DETECTED               = (uint16_t)0x0010,  /*!< STOPF flag */
    I2C_EVENT_SLAVE_BYTE_TRANSMITTED            = (uint16_t)0x0684,  /*!< TRA, BUSY, TXE and BTF flags */
    I2C_EVENT_SLAVE_BYTE_TRANSMITTING           = (uint16_t)0x0680,  /*!< TRA, BUSY and TXE flags */
    I2C_EVENT_SLAVE_ACK_FAILURE                 = (uint16_t)0x0004   /*!< AF flag */
} I2C_Event_TypeDef;

#endif

/*
 * board.h
 *
 *  Created on: 22 lis 2019
 *      Author: Igor
 */

#ifndef PERIPHERALS_BOARD_H_
#define PERIPHERALS_BOARD_H_

#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define ADC1_ENABLE     BIT4
#define ADC2_ENABLE     BIT5
#define ADC3_ENABLE     BIT6
#define ADC4_ENABLE     BIT7

#define ADC1_INPUT      BIT4        // A1
#define ADC2_INPUT      BIT3        // A2
#define ADC3_INPUT      BIT5        // A0
#define ADC4_INPUT      BIT2        // A3

#define BUTTON1         BIT1
#define BUTTON2         BIT2

// define LED pins as ouptuts and general purpose IOs
#define LED_INIT    (*((volatile unsigned char*)0x40004C65)) |=  BIT7;  \
                    (*((volatile unsigned char*)0x40004C6B)) &= ~BIT7;  \
                    (*((volatile unsigned char*)0x40004C6D)) &= ~BIT7;  \
                    (*((volatile unsigned char*)0x40004C84)) |=  BIT0;  \
                    (*((volatile unsigned char*)0x40004C8A)) &= ~BIT0;  \
                    (*((volatile unsigned char*)0x40004C8C)) &= ~BIT0;  \
                    (*((volatile unsigned char*)0x40004C45)) |=  BIT0;  \
                    (*((volatile unsigned char*)0x40004C4B)) &= ~BIT0;  \
                    (*((volatile unsigned char*)0x40004C4D)) &= ~BIT0;  \
                    (*((volatile unsigned char*)0x40004C84)) |=  BIT1;  \
                    (*((volatile unsigned char*)0x40004C8A)) &= ~BIT1;  \
                    (*((volatile unsigned char*)0x40004C8C)) &= ~BIT1;  \
//                    (*((volatile unsigned char*)0x40004C43)) |=  BIT0;  \
//                    (*((volatile unsigned char*)0x40004C82)) |=  BIT1;  \
//                    (*((volatile unsigned char*)0x40004C63)) |=  BIT7;  \
//                    (*((volatile unsigned char*)0x40004C82)) |=  BIT0;  \

// define LED1 modes
#define LED1_ON     (*((volatile unsigned char*)0x40004C43)) &= ~BIT0
#define LED1_OFF    (*((volatile unsigned char*)0x40004C43)) |=  BIT0
#define LED1_TOGGLE (*((volatile unsigned char*)0x40004C43)) ^=  BIT0
// define LED2 modes
#define LED2_ON     (*((volatile unsigned char*)0x40004C82)) &= ~BIT1
#define LED2_OFF    (*((volatile unsigned char*)0x40004C82)) |=  BIT1
#define LED2_TOGGLE (*((volatile unsigned char*)0x40004C82)) ^=  BIT1
// define LED3 modes
#define LED3_ON     (*((volatile unsigned char*)0x40004C63)) &= ~BIT7
#define LED3_OFF    (*((volatile unsigned char*)0x40004C63)) |=  BIT7
#define LED3_TOGGLE (*((volatile unsigned char*)0x40004C63)) ^=  BIT7
// define LED4 modes
#define LED4_ON     (*((volatile unsigned char*)0x40004C82)) &= ~BIT0
#define LED4_OFF    (*((volatile unsigned char*)0x40004C82)) |=  BIT0
#define LED4_TOGGLE (*((volatile unsigned char*)0x40004C82)) ^=  BIT0



#endif /* PERIPHERALS_BOARD_H_ */

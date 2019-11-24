/*
 * button.c
 *
 *  Created on: 21 lis 2019
 *      Author: Igor
 */

#include "peripherals/button.h"
#include "peripherals/uart.h"


buttonController button1;
buttonController button2;

extern int flag;




void buttonInit(void)
{
    P3->DIR  &= ~(BUTTON1 | BUTTON2);   // set as input
    P3->IES  &= ~(BUTTON1 | BUTTON2);   // high-to-low transition interrupt
    P3->SEL0 &= ~(BUTTON1 | BUTTON2);   // specify pin as GPIO only
    P3->SEL1 &= ~(BUTTON1 | BUTTON2);   // specify pin as GPIO only
    P3->IFG  &= ~(BUTTON1 | BUTTON2);   // clear interrupt flag
    P3->IE   |=   BUTTON1 | BUTTON2;    // enable interrupt

    button1.isPressValid = false;
    button1.pushTimeStamp = 0;
    button1.shortPressCount = 0;

    button2.isPressValid = false;
    button2.pushTimeStamp = 0;
    button2.shortPressCount = 0;
}

// Interrupt handler

void PORT3_IRQHandler(void)
{
    puts("Putton has beeen pressed");
    if(P3->IFG & BIT1)
        P3->IFG &= ~BIT1;
    if(P3->IFG & BIT2)
        P3->IFG &= ~BIT2;
    flag ^=0x01;
}








/*
 * uart.c
 *
 *  Created on: 23 lis 2019
 *      Author: Igor
 */

#include "peripherals/uart.h"

void uart(void)
{
    EUSCI_A0->CTLW0 |=  UCSWRST;
    EUSCI_A0->MCTLW = 0;
    EUSCI_A0->CTLW0 =   EUSCI_A_CTLW0_SWRST |                       // Remain eUSCI in reset
                        EUSCI_B_CTLW0_SSEL__SMCLK;
    EUSCI_A0->BRW = 1;                                              // set Baud Rate to 460800
    EUSCI_A0->MCTLW =   (10 << EUSCI_A_MCTLW_BRF_OFS) |
                        EUSCI_A_MCTLW_OS16;
    P1->SEL0 |= BIT2 | BIT3;                                        // selet UART pins
    P1->SEL1 &= ~(BIT2 | BIT3);
    EUSCI_A0->CTLW0 &= ~UCSWRST;
}

void uartSendString(char *string)
{
    while(*string)
    {
        while(!(EUSCI_A0->IFG & UCTXIFG));
        EUSCI_A0->TXBUF = *string++;
    }
}







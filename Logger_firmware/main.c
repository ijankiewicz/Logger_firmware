#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "peripherals/button.h"
#include "peripherals/adc.h"
#include "peripherals/board.h"
#include "peripherals/uart.h"


uint16_t temp, temp2;
uint8_t flag = 0;

/**
 * main.c
 */
void main(void)
{

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer


	buttonInit();
	LED1_ON;
    LED2_ON;
    LED3_ON;
    LED4_ON;

    CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
    CS->CTL2 |= CS_CTL2_LFXT_EN;            // LFXT on
    CS->CTL2 |= CS_CTL2_HFXT_EN;
    CS->KEY = 0;

    CS->KEY = CS_KEY_VAL ;                                          // Unlock CS module for register access
    CS->CTL0 = 0;                                                   // Reset tuning parameters
    CS->CTL0 = CS_CTL0_DCORSEL_3;                                   // Set DCO to 12MHz (nominal, center of 8-16MHz range)
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;    // Select ACLK = REFO, SMCLK = MCLK = DCO
    CS->KEY = 0;



    // Select ACLK as LFXTCLK
    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELA_MASK | CS_CTL1_DIVA_MASK) | CS_CTL1_SELA_0;
    CS->KEY = 0;                            // Lock CS module from unintended accesses


    __enable_irq();
    NVIC->ISER[0] = 1 << ((TA1_0_IRQn) & 31);
    NVIC->ISER[0] = 1 << ((TA1_N_IRQn) & 31);
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);
    NVIC->ISER[1] = 1 << ((PORT3_IRQn) & 31);

    adcInit();
    adcConfig();
    uart();

    uartSendString("***** Data Acquisition Board v1.0 - PIEZO PROJECT *****\r\n");
    uartSendString("*****      Copyright - Igor Jankiewicz (2019)     *****\r\n");
    uartSendString("\r\n");
    uartSendString("\r\n");
    uartSendString("Board initalization...\r\n");
    uartSendString("\r\n");
    uartSendString("UART Baud Rate fixed at 460800bps\r\n");
    uartSendString("\r\n");
    adcChannel_scan();


    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    TIMER_A1->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A1->CCR[0] = 32768 - 1;
    TIMER_A1->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG;
    TIMER_A1->CCTL[1] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A1->CCR[1] = 16384-1;
    TIMER_A1->CTL |= TIMER_A_CTL_TASSEL_1 | // ACLK
            TIMER_A_CTL_MC_1;               // up mode


	P6->DIR |=(BIT3 | BIT4 | BIT5 | BIT6);
	P6->OUT |=(BIT3 | BIT4 | BIT5 | BIT6);

    LED_INIT;

    puts("LEDs initialized...");



    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;

    while(1)
    {
        if(flag)
        {
            ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
            while(!(ADC14->CTL0 & ADC14_CTL0_BUSY));
            while(!(EUSCI_A0->IFG & UCTXIFG));
            EUSCI_A0->TXBUF = temp;
            while(!(EUSCI_A0->IFG & UCTXIFG));
            EUSCI_A0->TXBUF = (temp >> 8);
            while(!(EUSCI_A0->IFG & UCTXIFG));
            EUSCI_A0->TXBUF = temp2;
            while(!(EUSCI_A0->IFG & UCTXIFG));
            EUSCI_A0->TXBUF = (temp2 >> 8);

        }
        else
            ADC14->CTL0 &= ~ADC14_CTL0_SC;

        __sleep();
    }
}



void TA1_0_IRQHandler(void) {
    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    TIMER_A1->CCR[0] += 32768;

    //uartSendString("1 sec timer ticks\r\n");


}

void TA1_N_IRQHandler(void) {
    TIMER_A1->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG;
    TIMER_A1->CCR[1] += 16384-1;
}

void ADC14_IRQHandler(void)
{

    if (ADC14->IFGR0 & ADC14_IFGR0_IFG1)
    {
        temp = ADC14->MEM[0];
        temp2 = ADC14->MEM[1];
    }
}





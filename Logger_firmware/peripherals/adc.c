/*
 * adc.c
 *
 *  Created on: 21 lis 2019
 *      Author: Igor
 */

#include "peripherals/adc.h"
#include "peripherals/uart.h"

void adcInit (void)
{
    // ADC seelction input pins
    P7->DIR  &= ~(ADC4_ENABLE | ADC3_ENABLE | ADC2_ENABLE | ADC4_ENABLE);   // set as input
    P7->SEL0 &= ~(ADC4_ENABLE | ADC3_ENABLE | ADC2_ENABLE | ADC4_ENABLE);   // specify pin as GPIO only
    P7->SEL1 &= ~(ADC4_ENABLE | ADC3_ENABLE | ADC2_ENABLE | ADC4_ENABLE);   // specify pin as GPIO only

    // ADC input channels
    P5->SEL0 |= (ADC1_INPUT | ADC2_INPUT | ADC3_INPUT | ADC4_INPUT);        // specify these pins as analog inputs
    P5->SEL1 |= (ADC1_INPUT | ADC2_INPUT | ADC3_INPUT | ADC4_INPUT);

    P5->SEL1 |= BIT6 | BIT7;         // Enable A/D channel A0
    P5->SEL0 |= BIT6 | BIT7;         // and VeREF+ and VeREF-
}

void adcChannel_scan(void)
{
    adcChannel adcEnable;

    adcEnable.adcChannel_1 = false;
    adcEnable.adcChannel_2 = false;
    adcEnable.adcChannel_3 = false;
    adcEnable.adcChannel_4 = false;

    uartSendString("ADC input detecting...\r\n");
    uartSendString("\r\n");

    if(!(P7->IN & ADC1_ENABLE))
    {
        adcEnable.adcChannel_1 = true;
        uartSendString("ADC channel 1 - enabled\r\n");
    }
    else
        uartSendString("ADC channel 1 - disabled\r\n");


    if(!(P7->IN & ADC2_ENABLE))
    {
        adcEnable.adcChannel_2 = true;
        uartSendString("ADC channel 2 - enabled\r\n");
    }
    else
        uartSendString("ADC channel 2 - disabled\r\n");

    if(!(P7->IN & ADC3_ENABLE))
    {
        adcEnable.adcChannel_3 = true;
        uartSendString("ADC channel 3 - enabled\r\n");
    }
    else
        uartSendString("ADC channel 3 - disabled\r\n");

    if(!(P7->IN & ADC4_ENABLE))
    {
        adcEnable.adcChannel_4 = true;
        uartSendString("ADC channel 4 - enabled\r\n");
    }
    else
        uartSendString("ADC channel 4 - disabled\r\n");


}

void adcConfig(void)
{


    ADC14->CTL0 &= ~ADC14_CTL0_ENC;                                 // disable ADC14
    ADC14->CTL0 |=  ADC14_CTL0_ON |                                 // switch ADC14 on
                    ADC14_CTL0_DIV__3 |
                    ADC14_CTL0_MSC |
                    ADC14_CTL0_SHT0__192 |                          // set SHT
                    ADC14_CTL0_CONSEQ_3 |                           // consequtive, single channel
                    ADC14_CTL0_SHP |
                    ADC14_CTL0_SSEL_3;                                 // SAMPCON sourced from sampling timer
    ADC14->CTL1 |=  ADC14_CTL1_RES_3/*|                               // resolution = 14 bit
                    (ADC14->CTL1 & ~ADC14_CTL1_CSTARTADD_MASK) | (0 << ADC14_CTL1_CSTARTADD_OFS)*/; // CSTARTADD=5; here put number related to the last MCLT[x]
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_1 | ADC14_MCTLN_VRSEL_14;                                         // A1 as analog input
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_2 | ADC14_MCTLN_VRSEL_14 | ADC14_MCTLN_EOS;                       // A2 as analog input



    ADC14->IER0 = ADC14_IER0_IE1;                                  // Enable ADC14IFG.5
}







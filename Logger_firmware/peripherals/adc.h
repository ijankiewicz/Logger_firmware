/*
 * adc.h
 *
 *  Created on: 21 lis 2019
 *      Author: Igor
 */

#ifndef PERIPHERALS_ADC_H_
#define PERIPHERALS_ADC_H_

#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "peripherals/board.h"


typedef struct
{
    bool adcChannel_1;
    bool adcChannel_2;
    bool adcChannel_3;
    bool adcChannel_4;

} adcChannel;

void adcInit(void);
void adcConfig(void);
void adcChannel_scan(void);

#endif /* PERIPHERALS_ADC_H_ */

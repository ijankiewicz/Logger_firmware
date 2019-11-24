/*
 * button.h
 *
 *  Created on: 21 lis 2019
 *      Author: Igor
 */
#ifndef PERIPHERALS_BUTTON_H_
#define PERIPHERALS_BUTTON_H_

#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "peripherals/board.h"


typedef struct
{
    bool        isPressValid;
    uint32_t    pushTimeStamp;
    uint8_t     shortPressCount;

} buttonController;

void buttonInit(void);



#endif /* PERIPHERALS_BUTTON_H_ */

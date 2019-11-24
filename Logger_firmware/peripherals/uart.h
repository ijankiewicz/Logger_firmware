/*
 * uart.h
 *
 *  Created on: 23 lis 2019
 *      Author: Igor
 */

#ifndef PERIPHERALS_UART_H_
#define PERIPHERALS_UART_H_

#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

void uart(void);
void uartSendString(char *string);





#endif /* PERIPHERALS_UART_H_ */

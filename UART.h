/*
 * UART.h
 *
 *  Created on: 30 sep 2022
 *      Author: rober
 */

#ifndef UART_H_
#define UART_H_


void UART0_Init(void);
void txchar(char c);

void UART_OutString(char *pt);
void UART_OutUDec(uint32_t n);
void UART_OutUFloat(float n,int dec);



#endif /* UART_H_ */

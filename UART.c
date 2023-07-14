/*
 * UART.c
 *
 *  Created on: 30 sep 2022
 *      Author: rober
 */

#include<stdio.h>
#include<stdint.h>
#include<math.h>
#include"tm4c.h"
#include"UART.h"



void UART0_Init(void)
{
    SYSCTL_RCGCUART_R |= 0x01;
    while((SYSCTL_PRUART_R & 0x01)==0);//Wait for activation
    SYSCTL_RCGCGPIO_R |= 0x01;
    while((SYSCTL_PRGPIO_R & 0x01)==0);//Wait for activation
    UART0_CTL_R &= ~(0x01);
    GPIO_PORTA_AHB_AFSEL_R |= 0x03;
    GPIO_PORTA_AHB_PUR_R &= ~(0x03);
    GPIO_PORTA_AHB_PDR_R &= ~(0x03);
    GPIO_PORTA_AHB_DIR_R &= ~(0x01);
    GPIO_PORTA_AHB_DIR_R |= ~(0x02);
    GPIO_PORTA_AHB_PCTL_R |= (GPIO_PORTA_AHB_PCTL_R & 0xFFFFFF00) | 0x00000011;
    GPIO_PORTA_AHB_DEN_R |= 0x03;
    UART0_IBRD_R=(UART0_IBRD_R & ~0xFFFF)|0x68;
    UART0_FBRD_R = (UART0_FBRD_R & ~0x3F) | 0xB;
    UART0_LCRH_R = (UART0_LCRH_R & ~0xFF) | 0x70;
    UART0_CTL_R &= ~0x20;
    UART0_CTL_R |= 0x301;
    while((UART0_FR_R & UART_FR_TXFF)!=0);
    //UART0_DR_R = c;



}
void txchar(char c)
{
    while ((UART0_FR_R & UART_FR_TXFF)!=0);
    UART0_DR_R=c;
}
/* Output String (NULL termination), Input: pointer to a NULL-terminated string to be transferred, Output: none */
void UART_OutString(char *pt)
{
  while(*pt){
    txchar(*pt);
    pt++;
  }
}

/* ============================ UART_OutUDec ============================ */
/* Output a 32-bit number in unsigned decimal format, Input: 32-bit number to be transferred, Output: none
   Variable format 1-10 digits with no space before or after */
void UART_OutUDec(uint32_t n)
{
/*This function uses recursion to convert decimal number of unspecified length as an ASCII string */
  if(n >= 10){
    UART_OutUDec(n/10);
    n = n%10;
  }
  txchar(n+'0');                                           /* n is between 0 and 9 */
}
void UART_OutUFloat(float n,int dec)
{
    int i,m;
    if(n<0)
    {
        UART_OutString("-");
        n=n*-1;
    }
    if(n>=1)
    {
        UART_OutUDec(n);

    }
    else
    {
        UART_OutUDec(0);
    }
    UART_OutString(".");

    for(i=0;i<dec;i++)
    {
        m=(n-(int)n)*pow(10,i+1);
        while(m>=10)
        {
            m=m%10;
        }
        UART_OutUDec(m);

    }
    //LCD_OutUDec(m);

}

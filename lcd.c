/*
 * lcd.c
 *
 *  Created on: 18 sep 2022
 *      Author: rober
 */
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include"tm4c.h"
#include"lcd.h"

/* ============================ LCD commands function ============================ */
void OutCmd(unsigned char command){ //RS= PH0 = 0x01  E=PH1= 0x02
  GPIO_PORTH_AHB_DATA_R = 0x00;
  GPIO_PORTK_DATA_R = command;                                             /* E=0, R/W=0, RS=0 */
  CtlDelay(240);                                         /* SysTick_Wait(T6us); wait 6us */
  GPIO_PORTH_AHB_DATA_R = E;                                               /* E=1, R/W=0, RS=0 */
  CtlDelay(240);                                         /* SysTick_Wait(T6us); wait 6us */
  GPIO_PORTH_AHB_DATA_R = 0;                                               /* E=0, R/W=0, RS=0 */
  CtlDelay(1600);                                            /* SysTick_Wait(T40us); wait 40us */
}

/* ============================ LCD Character function ============================ */
/* Output a character to the LCD, Inputs: letter is ASCII character, 0 to 0x7F, Outputs: none */
void LCD_OutChar(unsigned char letter){
  GPIO_PORTH_AHB_DATA_R  = RS;
  GPIO_PORTK_DATA_R = letter;                                            /* E=0, R/W=0, RS=1 */
  CtlDelay(240);                                         /* SysTick_Wait(T6us); wait 6us */
  GPIO_PORTH_AHB_DATA_R  = E+RS;                                            /* E=1, R/W=0, RS=1 */
  CtlDelay(240);                                         /* SysTick_Wait(T6us); wait 6us */
  GPIO_PORTH_AHB_DATA_R  = 0x00;                                              /* E=0, R/W=0, RS=1 */
  CtlDelay(1600);                                            /* SysTick_Wait(T40us); wait 40us */
}

/*============================ Clear the LCD, Inputs: none, Outputs: none ============================ */
void LCD_Clear(void){
  OutCmd(0x01);                                             /* Clear Display */
  CtlDelay(64000);                                           /* SysTick_Wait(T1600us); wait 1.6ms */
  OutCmd(0x02);                                             /* Cursor to home */
  CtlDelay(64000);                                           /* SysTick_Wait(T1600us); wait 1.6ms */

}

/* ============================ LCD_OutString ============================  */
/* Output String (NULL termination), Input: pointer to a NULL-terminated string to be transferred, Output: none */
void LCD_OutString(char *pt){
  while(*pt){
    LCD_OutChar(*pt);
    pt++;
  }
}

/* ============================ LCD_OutUDec ============================ */
/* Output a 32-bit number in unsigned decimal format, Input: 32-bit number to be transferred, Output: none
   Variable format 1-10 digits with no space before or after */
void LCD_OutUDec(uint32_t n){
/*This function uses recursion to convert decimal number of unspecified length as an ASCII string */
  if(n >= 10){
    LCD_OutUDec(n/10);
    n = n%10;
  }
  LCD_OutChar(n+'0');                                           /* n is between 0 and 9 */
}
void LCD_OutUFloat(float n,int dec)
{
    int i,m;
    if(n<0)
    {
        LCD_OutString("-");
        n=n*-1;
    }
    if(n>=1)
    {
        LCD_OutUDec(n);

    }
    else
    {
        LCD_OutUDec(0);
    }
    LCD_OutString(".");

    for(i=0;i<dec;i++)
    {
        m=(n-(int)n)*pow(10,i+1);
        while(m>=10)
        {
            m=m%10;
        }
        LCD_OutUDec(m);

    }
    //LCD_OutUDec(m);

}
void CtlDelay(uint32_t n)
{
    int i;
    for(i=0;i<n;i++)
    {

    }
}

volatile uint32_t ui32SysClkFreq;

void PortFunctionInit(void){
    volatile uint32_t ui32Loop;
    //ui32SysClkFreq = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
                                                    /* 120MHz */
    //SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_GPION;
    //SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R9|SYSCTL_RCGCGPIO_R4|SYSCTL_RCGCGPIO_R12;
    SYSCTL_RCGCGPIO_R   |= 0x0200 | 0x0080 | 0x1000;         //Star PORTD, PORTE, PORTN
                                                    /* Do a dummy read to insert a few cycles after
                                                    enabling the peripheral */
/* ============================ GPIO Port configuration ============================ */
    ui32Loop = SYSCTL_RCGCGPIO_R;
    GPIO_PORTN_DIR_R |= 0x01;                                   /* PN0 direction as output */
    GPIO_PORTN_DEN_R |= 0x01;                                   /* PN0 data enable */

    GPIO_PORTK_DIR_R |= 0xFF;
    GPIO_PORTH_AHB_DIR_R |= 0x03;
    GPIO_PORTK_DEN_R |= 0xFF;                                    /* enable digital port */
    GPIO_PORTH_AHB_DEN_R |= 0x03;
    GPIO_PORTK_DATA_R = 0x00;
    GPIO_PORTH_AHB_DATA_R = 0x00;
    //GPIO_PORTD_AHB_DR8R_R = 0xFF;                                   /* enable 8 mA drive */
    //GPIO_PORTE_AHB_DR8R_R |= 0x30;

/* ============================ LCD controller initilization ============================ */
    //LCDCMD = 0;                                         /* E=0, R/W=0, RS=0 */
    CtlDelay(600000);                                        /* Wait >15 ms after power is applied */
    OutCmd(0x38);                                           /* command 0x30 = Wake up */
    CtlDelay(200000);                                        /*must wait 5ms, busy flag not available */
    OutCmd(0x06);                                           /* command 0x30 = Wake up #2 */
    CtlDelay(6400);                                      /* must wait 160us, busy flag not available */
    OutCmd(0x0F);                                           /* command 0x30 = Wake up #3 */
    CtlDelay(6400);                                      /* must wait 160us, busy flag not available */
    OutCmd(0x01);                                           /* Function set: 8-bit/2-line */
    CtlDelay(6400);
}




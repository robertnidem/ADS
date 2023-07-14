/*
 * lcd.h
 *
 *  Created on: 7 sep 2022
 *      Author: rober
 */

#ifndef LCD_H_
#define LCD_H_


/* ============================ Defined constants ============================ */
#define E  0x02                                             /* Enable on PE5 */
#define RS 0x01                                             /* Read Select (RS) on PE4 */
#define LCDDATA (*((volatile uint32_t *)0x4005B3FC))                           /* Parallel Data on PORTK (PK0 - PK7)  */
#define LCDCMD  (*((volatile uint32_t *)0x4005C3FC))                        /* Commands on PE5 and PE4 */

/* ============================ Function prototypes ============================ */
void OutCmd(unsigned char );
void LCD_OutChar(unsigned char );
void LCD_Clear(void);
void LCD_OutString(char* );
void LCD_OutUDec(uint32_t );
void PortFunctionInit(void);
void CtlDelay(uint32_t);
void LCD_OutUFloat(float n,int dec);



#endif /* LCD_H_ */

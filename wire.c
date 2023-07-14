/*
 * wire.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#include<stdint.h>
#include<stdbool.h>
#include"tm4c.h"
#include"wire.h"
#include"UART.h"

int TPR=7;

//Variables para manejar la conexion i2c
uint8_t err;
uint32_t i;
uint16_t i2cStatus;

void I2C0_Init(void){
    //CONFIGURACIÓN DE LOS RELOJ
    SYSCTL_RCGCGPIO_R |= 0x0002; // Activamos el reloj GPIO_PORTB mientras se activa el reloj de I2C0
    SYSCTL_RCGCI2C_R |= 0x0001; // Activamos el reloj de I2C0 [I2C9 I2C8 I2C7 ... I2C0]<--Mapa de RCGCI2C
    while((SYSCTL_PRGPIO_R&0x0002) == 0){};//Espero a que se active el reloj del puerto B

    //CONFIGURACIÓN DE LOS GPIOS
    /*Acorde con la tabla "Signals by function" de la p. 1808:
     el PIN 2 del puerto B (PB2) es el I2C0SCL del I2C0, y
     el PIN 3 del puerto B (PB3) es el I2C0SDA del I2C0
    */
    GPIO_PORTB_AFSEL_R |= 0xFF; // Activo la función alterna del PB2 y PB3
    GPIO_PORTB_ODR_R |= 0x08;   // Activo el OPEN DRAIN para el PB3, ya que el PB2 ya tiene uno por preconfig.
    //GPIO_PORTB_DIR_R |= 0x0C;   //Activo al PB2 y al PB3 como OUTPUT
    GPIO_PORTB_DEN_R |= 0x0C;   //Activo la función digital de PB3 y PB2

    GPIO_PORTB_PCTL_R|=0x00002200;

    //CONFIGURACIÓN DEL MODULO I2C0
    I2C0_MCR_R = 0x00000010; // Habilitar función MASTER para el I2C0
    I2C0_MTPR_R = TPR; // Se establece una velocidad estándar de 100kbps
}

int esperar(){
    while(I2C0_MCS_R&0x00000001){}; //Espero a que la transmisión acabe
      if(I2C0_MCS_R&0x00000002==1){ //¿Hubo err?
          UART_OutString("I2C0 esperar \t");
          err=1;
          return err;
      };
      return 0;

}


bool I2C0ready()
{
    return I2C0_MCS_R&0x00000001;
}

void I2C0begin(uint16_t dir,uint16_t dirR)//Inicia la conexion con la dirección dir en el registro dirR
{
    I2C0_MSA_R=(dir<<1)&0xFE;

    I2C0_MDR_R=dirR&0x0FF;
    I2C0_MCS_R=(I2C_MCS_START|I2C_MCS_RUN);
    esperar();
    for(i=0;i<300;i++){} //Delay
    i2cStatus=0;

}


void I2C0write(int data) //Con la conexion iniciada escribe la informacion data en el registro seleccionado
{
    I2C0_MDR_R=data&0xFF;
    I2C0_MCS_R=I2C_MCS_RUN;
    esperar();
    for(i=0;i<300;i++){} //Delay
}

void I2C0writeS(int data)//Escribe el ultimo valor y termina la conexion con el dispositivo
{
    I2C0_MDR_R=data&0xFF;
    I2C0_MCS_R=(I2C_MCS_RUN|I2C_MCS_STOP);
    esperar();
    for(i=0;i<300;i++){} //Delay
    i2cStatus=0;
}
uint8_t I2C0read(uint16_t dir)//Lee el valor de la direccion a la que esta apuntando
{
    if(i2cStatus==0)
    {
        I2C0_MSA_R=(dir<<1)&0xFE;
        I2C0_MSA_R|=0x01&0xFF;
        I2C0_MCS_R=(I2C_MCS_START|I2C_MCS_RUN|I2C_MCS_ACK); // Condición de RESTART, corro, ack
        i2cStatus=1;
    }
    else
    {
        I2C0_MCS_R=(I2C_MCS_RUN|I2C_MCS_ACK); // Condición de RESTART, corro, ack
    }
    esperar();
    for(i=0;i<300;i++){} //Delay
    return (I2C0_MDR_R)&0xFF;

}

void I2C0stop()//Termina la comunicacion con el dispositivo
{
    I2C0_MCS_R=(I2C_MCS_STOP|I2C_MCS_RUN);
    esperar();
    for(i=0;i<300;i++){} //Delay
    i2cStatus=0;
}









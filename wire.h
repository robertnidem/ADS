/*
 * wire.h
 *
 *  Created on: 27 jul 2022
 *      Author: rober
 */

#ifndef WIRE_H_
#define WIRE_H_

#include<stdbool.h>

void I2C0_Init(void);
int esperar();

bool I2C0ready();
void I2C0begin(uint16_t dir,uint16_t dirR);//Inicia la conexion con la dirección dir en el registro dirR



void I2C0write(int data); //Con la conexion iniciada escribe la informacion data en el registro seleccionado

void I2C0writeS(int data);//Escribe el ultimo valor y termina la conexion con el dispositivo
uint8_t I2C0read(uint16_t dir);//Lee el valor de la direccion a la que esta apuntando
void I2C0stop();//Termina la comunicacion con el dispositivo







#endif /* WIRE_H_ */

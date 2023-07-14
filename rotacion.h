/*
 * rotacion.h
 *
 *  Created on: 25 abr 2022
 *      Author: rober
 */

#ifndef ROTACION_H_
#define ROTACION_H_



MATRIZ ROT_X(float ang);

MATRIZ ROT_Y(float ang);
MATRIZ ROT_Z(float ang);

MATRIZ c2rot(QUAT a); //convertir un cuaternion a matriz de rotacion
QUAT StanCuat(MATRIZ r,float q, int i);//Metodo utilizado en la funcion anterior
QUAT rot2c(MATRIZ a);//convertir una matriz de rotación en cuaternion

#endif /* ROTACION_H_ */

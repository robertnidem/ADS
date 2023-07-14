/*
 * matrix.h
 *
 *  Created on: 7 abr 2022
 *      Author: rober
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include<stdbool.h>
#include<structs.h>



//MATRIZ error={NULL,{0,0},0,1};

MATRIZ Minit(int a, int b); //INICIA LA MATRIZ RECIBE LAS DIMENSIONES REGRESA ESTRUCTURA
MATRIZ Masign(MATRIZ A,float *m); //Asigna la matriz m a la estructura
MATRIZ Zeros(MATRIZ a); // Asigna el valor cero a toda la matriz
MATRIZ MinitZ(int dimx, int dimy);
MATRIZ Mrand(int dimx, int dimy);
MATRIZ Meye(int dim);

MATRIZ Msum(MATRIZ a, MATRIZ b); //Suma de dos matrices
MATRIZ Mres(MATRIZ a, MATRIZ b); //Resta de dos matrices
MATRIZ Mmul(MATRIZ a, MATRIZ b);//Multiplicación de matrices, mxn oxp,  si n=o resulta mxp
MATRIZ Mmules(float es,MATRIZ a);
float Mdet(MATRIZ a); //Determinante de una matriz
MATRIZ Mcof(MATRIZ a, int i, int j);//Matriz de cofactores de la matriz a
MATRIZ Madj(MATRIZ a);//Matriz adjunta de a, probada en 3x3
MATRIZ Mcrz(MATRIZ a,MATRIZ b);//Producto cruz definido para vectores columna

MATRIZ Mtrans(MATRIZ a);//Matriz transpuesta
MATRIZ Minv(MATRIZ a);//Matriz inversa

float Mtraza(MATRIZ a);//Traza de la matriz

MATRIZ vec2m(VECTOR a);//convertir vector (3x1) en matriz (3x1)
VECTOR m2vec(MATRIZ a);//convertir matriz (3x1) en vector (3x1)
QUAT m2q(MATRIZ a);//convertir una matriz de rotacion en un cuaternion

#endif /* MATRIX_H_ */

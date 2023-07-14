/*
 * estimadores.h
 *
 *  Created on: 26 abr 2022
 *      Author: rober
 */

#ifndef ESTIMADORES_H_
#define ESTIMADORES_H_


MATRIZ TRIAD(VECTOR rs, VECTOR rm, VECTOR s,VECTOR m);
float func(float fun[],int dim, float l0);
float dfunc(float fun[],int dim,float l0);

float NwtRhp(float fun[], int pres, int dim, float l0);
QUAT QUEST(VECTOR rmag, VECTOR rsol, VECTOR mag, VECTOR sol);
VECTOR estSol(time_stat time);

parOrb propOrb(parOrb para, float t, float t0);

#endif /* ESTIMADORES_H_ */

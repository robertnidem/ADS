/*
 * vector.h
 *
 *  Created on: 5 abr 2022
 *      Author: rober
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include"structs.h"

//VECTOR Verror={NULL,0};

int size(float a[]);

VECTOR Vinit(int dim);

VECTOR Vasign(VECTOR a,float *v);
VECTOR Vcrz(VECTOR a, VECTOR b);
float Vdot(VECTOR a, VECTOR b);
float Vmod(VECTOR a);

VECTOR Vnorm(VECTOR a);

float ent(float n);


#endif /* VECTOR_H_ */

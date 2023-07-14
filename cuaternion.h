/*
 * cuaternion.h
 *
 *  Created on: 25 abr 2022
 *      Author: rober
 */

#ifndef CUATERNION_H_
#define CUATERNION_H_



//#define PI 3.1415926535897

//#define cosd(ang) cos(((ang)*(PI))/180)
//#define sind(ang) sin(((ang)*(PI))/180)



QUAT Cuat(VECTOR a,float ang);
QUAT Ccon(QUAT a);
QUAT Csum(QUAT a, QUAT b);
QUAT Cres(QUAT a, QUAT b);
QUAT Cmul(QUAT a, QUAT b);
QUAT Cerr(QUAT a,QUAT b);
float Cmod(QUAT a);
QUAT Cnorm(QUAT a);

#endif /* CUATERNION_H_ */

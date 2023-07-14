/*
 * cuaternion.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include"vector.h"
#include"matrix.h"

QUAT Cuat(VECTOR a,float ang)
{
    QUAT c;
    c.q[0]=a.p[0]*sind((ang/2));
    c.q[1]=a.p[1]*sind((ang/2));
    c.q[2]=a.p[2]*sind((ang/2));
    c.q[3]=cosd((ang/2));
    return c;
}

QUAT Ccon(QUAT a)
{
    QUAT c;
    c.q[0]=-a.q[0];
    c.q[1]=-a.q[1];
    c.q[2]=-a.q[2];
    c.q[3]=a.q[3];
    return c;
}

QUAT Csum(QUAT a, QUAT b)
{
    QUAT c;
    int i;
    for(i=0;i<4;i++)
    {
        c.q[i]=a.q[i]+b.q[i];

    }
    return c;
}
QUAT Cres(QUAT a, QUAT b)
{
    QUAT c;
    int i;
    for(i=0;i<4;i++)
    {
        c.q[i]=a.q[i]-b.q[i];

    }
    return c;
}

QUAT Cmul(QUAT a, QUAT b)
{
    QUAT c;
    c.q[0]=a.q[3]*b.q[0]+b.q[3]*a.q[0]+a.q[1]*b.q[2]-a.q[2]*b.q[1];
    c.q[1]=a.q[1]*b.q[3]+a.q[3]*b.q[1]+a.q[2]*b.q[0]-a.q[0]*b.q[2];
    c.q[2]=a.q[2]*b.q[3]+a.q[3]*b.q[2]-a.q[1]*b.q[0]+a.q[0]*b.q[1];
    c.q[3]=a.q[3]*b.q[3]-a.q[0]*b.q[0]-a.q[1]*b.q[1]-a.q[2]*b.q[2];

    return c;
}
QUAT Cerr(QUAT a,QUAT b)
{

    QUAT c;
    c.q[0]=a.q[0]*b.q[3]+b.q[2]*a.q[1]-b.q[1]*a.q[2]-b.q[0]*a.q[3];
    c.q[1]=-b.q[2]*a.q[0]+b.q[3]*a.q[1]+b.q[0]*a.q[2]-b.q[1]*a.q[3];
    c.q[2]=b.q[1]*a.q[0]-b.q[0]*a.q[1]+b.q[3]*a.q[2]-b.q[2]*a.q[3];
    c.q[3]=a.q[0]*b.q[0]+a.q[1]*b.q[1]+a.q[2]*b.q[2]+a.q[3]*a.q[3];
    return c;
}

float Cmod(QUAT a)
{
    return sqrt(pow(a.q[0],2)+pow(a.q[1],2)+pow(a.q[2],2)+pow(a.q[3],2));
}
QUAT Cnorm(QUAT a)
{
    a.q[0]=a.q[0]/Cmod(a);
    a.q[1]=a.q[1]/Cmod(a);
    a.q[2]=a.q[2]/Cmod(a);
    a.q[3]=a.q[3]/Cmod(a);
    return a;
}





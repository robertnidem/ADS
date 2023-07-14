/*
 * rotacion.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include"structs.h"
#include"vector.h"
#include"matrix.h"
#include"rotacion.h"

extern int memoria;

MATRIZ ROT_X(float ang)
{
    MATRIZ a=Minit(3,3);
    //ang=rad(ang);
    float *pc, c[3][3]={{1,0,0},{0,cosd(ang),-sind(ang)},{0, sind(ang),cosd(ang)}};
    pc=c;
    a=Masign(a,pc);
    return a;
}

MATRIZ ROT_Y(float ang)
{
    MATRIZ a=Minit(3,3);
    float *pc,c[3][3]={{cosd(ang),0,sind(ang)},{0,1,0},{-sind(ang),0,cosd(ang)}};
    pc=c;

    a=Masign(a,pc);
    return a;
}
MATRIZ ROT_Z(float ang)
{
    MATRIZ a=Minit(3,3);
    float *pc, c[3][3]={{cosd(ang),-sind(ang),0},{sind(ang),cosd(ang),0},{0,0,1}};
    pc=c;
    a=Masign(a,pc);
    return a;
}

MATRIZ c2rot(QUAT a)
{
    MATRIZ b=Minit(3,3);
    float *pc,c[3][3];
    c[0][0]=a.q[3]*a.q[3]+a.q[0]*a.q[0]-a.q[1]*a.q[1]-a.q[2]*a.q[2];
    c[0][1]=2*a.q[0]*a.q[1]-2*a.q[3]*a.q[2];
    c[0][2]=2*a.q[0]*a.q[2]+2*a.q[3]*a.q[1];
    c[1][0]=2*a.q[0]*a.q[1]+2*a.q[3]*a.q[2];
    c[1][1]=a.q[3]*a.q[3]-a.q[0]*a.q[0]+a.q[1]*a.q[1]-a.q[2]*a.q[2];
    c[1][2]=2*a.q[1]*a.q[2]-2*a.q[0]*a.q[3];
    c[2][0]=2*a.q[0]*a.q[2]-2*a.q[1]*a.q[3];
    c[2][1]=2*a.q[1]*a.q[2]+2*a.q[0]*a.q[3];
    c[2][2]=a.q[3]*a.q[3]-a.q[0]*a.q[0]-a.q[1]*a.q[1]+a.q[2]*a.q[2];
    pc=c;
    b=Masign(b,pc);



    return b;
}
QUAT StanCuat(MATRIZ r,float q, int i)
{
    QUAT qr={{0,0,0,0},0};
    switch (i)
    {

    case 0:
        qr.q[0]=q;
        qr.q[1]=(r.p[1][0]+r.p[0][1])/(4*q);
        qr.q[2]=(r.p[0][2]+r.p[2][0])/(4*q);
        qr.q[3]=(r.p[2][1]-r.p[1][2])/(4*q);

        break;

    case 1:
        qr.q[0]=(r.p[0][1]+r.p[1][0])/(4*q);
        qr.q[1]=q;
        qr.q[2]=(r.p[1][2]+r.p[2][1])/(4*q);
        qr.q[3]=(r.p[0][2]-r.p[2][0])/(4*q);

        break;

    case 2:
        qr.q[0]=(r.p[2][0]+r.p[0][2])/(4*q);
        qr.q[1]=(r.p[1][2]+r.p[2][1])/(4*q);
        qr.q[2]=q;
        qr.q[3]=(r.p[1][0]-r.p[0][1])/(4*q);
        break;

    case 3:
        qr.q[0]=(r.p[2][1]-r.p[1][2])/(4*q);
        qr.q[1]=(r.p[0][2]-r.p[2][0])/(4*q);
        qr.q[2]=(r.p[1][0]-r.p[0][1])/(4*q);
        qr.q[3]=q;
        break;

    }
    return qr;
}
QUAT rot2c(MATRIZ a)
{
    QUAT c={{0,0,0,0},0};
    float q[4];
    q[0]=sqrt(fabs((1+a.p[0][0]-a.p[1][1]-a.p[2][2])))*0.5;
    q[1]=sqrt(fabs((1-a.p[0][0]+a.p[1][1]-a.p[2][2])))*0.5;
    q[2]=sqrt(fabs((1-a.p[0][0]-a.p[1][1]+a.p[2][2])))*0.5;
    q[3]=sqrt(fabs((1+Mtraza(a))))*0.5;

    if (q[0]>=q[1])
    {
        if (q[0]>=q[2])
        {
            if (q[0]>=q[3])
            {
                //q0
                c=StanCuat(a,q[0],0);
            }
            else
            {
                //q3
                c=StanCuat(a,q[3],3);
            }
        }
        else
        {
            if (q[2]>=q[3])
            {
                //q2
                c=StanCuat(a,q[2],2);
            }
            else
            {
                //q3
                c=StanCuat(a,q[3],3);
            }

        }
    }
    else
    {
        if (q[1]>=q[2])
        {
            if (q[1]>=q[3])
            {
                //q1
                c=StanCuat(a,q[1],1);

            }
            else
            {
                //q3
                c=StanCuat(a,q[3],3);
            }

        }
        else
        {
            if (q[2]>=q[3])
            {
                //q2
                c=StanCuat(a,q[2],2);
            }
            else
            {
                //q3
                c=StanCuat(a,q[3],3);
            }
        }
    }
    if(a.willFree==0)
    {
        //free(a.p);
        memoria-=1;
    }


    return c;


}




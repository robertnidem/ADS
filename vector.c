/*
 * vector.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include"vector.h"
extern int memoria;
VECTOR Verror={NULL,0};

int size(float a[])
{
    return sizeof(a)/sizeof(a[0]);

}
VECTOR Vinit(dim)
{
    VECTOR a;
    a.dim=dim;
    //a.p=(float*)malloc(dim*sizeof(float));
    //float p[3];
    //a.p=p[0];
    //memoria+=1;
    /*if(a.p==NULL)
    {
        return Verror;
    }*/
    a.willFree=0;
    a.status=0;
    return a;
}
VECTOR Vasign(VECTOR a,float *v)
{
    int i;
    for(i=0;i<a.dim;i++)
    {
        a.p[i]=*(v+i);
    }
    return a;
}

VECTOR Vcrz(VECTOR a, VECTOR b)
{
    VECTOR c=Vinit(3);
    c.p[0] = a.p[1]*b.p[2]-a.p[2]*b.p[1];
    c.p[1] = a.p[2]*b.p[0]-a.p[0]*b.p[2];
    c.p[2] = a.p[0]*b.p[1]-a.p[1]*b.p[0];


    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }
    if(b.willFree==0)
    {
        //free(b.p);
        //memoria-=1;
    }

    return c;
}

float Vdot(VECTOR a, VECTOR b)
{
    int j=0;
    //int max=size(a);
    float c=0;
    for (j=0; j<a.dim; j++)
    {
        c=c+a.p[j]*b.p[j];
    }


    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }
    if(b.willFree==0)
    {
        //free(b.p);
        //memoria-=1;
    }

    return c;
}

float Vmod(VECTOR a)
{
    int i;
    float modA;
    modA=0;
    for(i=0;i<a.dim;i++)
    {
        modA=modA+pow(a.p[i],2);
    }

    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return sqrt(modA);
}


VECTOR Vnorm(VECTOR a)
{
    int status=0;
    VECTOR b=Vinit(a.dim);
    if(a.willFree==0)
    {
        status=1;
        a.willFree=1;
    }
    float mod;
    mod= Vmod(a);
    int i;
    for (i=0;i<a.dim;i++)
    {
        b.p[i]=a.p[i]/mod;
    }
    b.status=a.status;
    if(status==1)
    {
        status=0;
        a.willFree=0;
    }

    if(a.willFree==0)
    {
        //free(a.p);
        ////memoria-=1;
    }

    return b;

}

float ent(float n)
{
    double entero;
    modf(n,&entero);
    return entero;
}




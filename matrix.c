/*
 * matrix.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<math.h>
#include<structs.h>
#include"VECTOR.h"
#include"matrix.h"
#include"cuaternion.h"
#include"UART.h"

extern int memoria;


MATRIZ error={{{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}},{0,0},0,1};

MATRIZ Minit(int a, int b) //INICIA LA MATRIZ RECIBE LAS DIMENSIONES REGRESA ESTRUCTURA
{
    int k;
    MATRIZ A;
    A.dim[0]=a;
    A.dim[1]=b;
    A.willFree=0;
    A.status=0;
    /*float** p=(float **)malloc(A.dim[0] * sizeof(float*));
    memoria+=1;
    if(p==NULL)
        return error;
    for(k = 0; k < A.dim[0]; k++)
    {
        p[k]=(float *)malloc(A.dim[1]* sizeof(float));
    }
    if (p==NULL)
    {
        return error;
    }*/
    return A;
}
MATRIZ Masign(MATRIZ A,float *m)//Asigna la matriz m a la estructura
{
    int i,j;
    for(i=0;i<A.dim[0];i++)
    {
        for(j=0;j<A.dim[1];j++)
        {
            A.p[i][j]= *(m+j+i*A.dim[1]);
            //A.p[i][j]= m[i][j];
        }
    }
    return A;
}
MATRIZ Zeros(MATRIZ a) // Asigna el valor cero a toda la matriz
{

    int i,j;
    for(i=0;i<a.dim[0];i++)
    {
        for(j=0;j<a.dim[1];j++)
        {
            a.p[i][j]=0;
        }
    }
    return a;

}
MATRIZ MinitZ(int dimx, int dimy)
{
    MATRIZ a=Minit(dimx,dimy);
    int i,j;
        for(i=0;i<a.dim[0];i++)
        {
            for(j=0;j<a.dim[1];j++)
            {
                a.p[i][j]=0;
            }
        }
        return a;
}
MATRIZ Mrand(int dimx, int dimy)
{
    MATRIZ c=Minit(dimx, dimy);
    c.willFree=0;
    int i,j;
    for (i=0;i<dimx;i++)
    {
        for(j=0;j<dimy;j++)
        {
            c.p[i][j]=(rand()%100)/100.0f;
        }
    }
    return c;
}
MATRIZ Meye(int dim)
{
    MATRIZ a=MinitZ(dim,dim);
    int i;
    for(i=0;i<a.dim[0];i++)
    {
        a.p[i][i]=1;
    }
    return a;

}

MATRIZ Msum(MATRIZ a, MATRIZ b) //Suma de dos matrices
{
    int i,j;

    if(a.dim[0]==b.dim[0] && a.dim[1]==b.dim[1])
    {

        MATRIZ c=Minit(a.dim[0],a.dim[1]);

        for(i=0;i<a.dim[0];i++)
        {
            for(j=0;j<a.dim[1];j++)
            {
                c.p[i][j]=a.p[i][j]+b.p[i][j];
            }
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
    else
    {
        UART_OutString("Msum \t");
        return error;
    }
}
MATRIZ Mres(MATRIZ a, MATRIZ b) //Resta de dos matrices
{
    int i,j;

    if(a.dim[0]==b.dim[0] && a.dim[1]==b.dim[1])
    {

        MATRIZ c=Minit(a.dim[0],a.dim[1]);

        for(i=0;i<a.dim[0];i++)
        {
            for(j=0;j<a.dim[1];j++)
            {
                c.p[i][j]=a.p[i][j]-b.p[i][j];
            }
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
    else
    {
        UART_OutString("Mres \t");
        return error;
    }
}

MATRIZ Mmul(MATRIZ a, MATRIZ b)//Multiplicación de matrices, mxn oxp,  si n=o resulta mxp
{
    int i,j,k;
    if(a.dim[1]==b.dim[0])
    {
        MATRIZ c=Minit(a.dim[0],b.dim[1]);
        for(i=0;i<b.dim[1];i++)
        {
            for(j=0;j<a.dim[0];j++)
            {
                c.p[j][i]=0;
                for(k=0;k<a.dim[1];k++)
                {
                    c.p[j][i]+=a.p[j][k]*b.p[k][i];
                }
            }
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
    else
    {
        UART_OutString("Mmul \t");
        return error;
    }
    //free(c.p);

}

MATRIZ Mmules(float es,MATRIZ a)
{
    MATRIZ c=Minit(a.dim[0],a.dim[1]);
    int i,j;
    for (i=0;i<a.dim[0];i++)
    {
        for(j=0;j<a.dim[1];j++)
        {
            c.p[i][j]=es*a.p[i][j];
        }
    }

    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return c;
}

float Mdet(MATRIZ a) //Determinante de una matriz
{
    MATRIZ b=Minit(a.dim[0],a.dim[1]);//copia los datos de la matriz a en b, ya que será modificada
    float det=1, pivote, pivote1, aux;
    int i,j,k;

    for (i=0;i<b.dim[0];i++)
    {
        for(j=0;j<b.dim[1];j++)
        {
            b.p[i][j]=a.p[i][j];
        }
    }


    for (i=0;i<b.dim[0];i++)
    {
        pivote=b.p[i][i];
        for(j=i+1;j<b.dim[0];j++)
        {
            pivote1=b.p[j][i];
            aux=pivote1/pivote;
            for(k=0;k<b.dim[0];k++)
            {
                b.p[j][k]=b.p[j][k]-aux*b.p[i][k];
            }
        }
    }
    for(i=0;i<b.dim[0];i++)
    {
        det=det*b.p[i][i];
    }
    //free(b.p);
    //memoria-=1;
    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return det;
}

MATRIZ Mcof(MATRIZ a, int i, int j)//Matriz de cofactores de la matriz a
{
    MATRIZ sub=Minit(a.dim[0]-1,a.dim[0]-1);
    sub=Zeros(sub);
    int x,y,m,n;
    x=y=0;
    for(m=0;m<a.dim[0];m++)
    {
        for(n=0;n<a.dim[0];n++)
        {
            if(m!=i && n!=j)
            {
                sub.p[x][y]=a.p[m][n];
                y+=1;
                if(y==a.dim[0]-1)
                {
                    y=0;
                    x+=1;
                }
            }
        }
    }

    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return sub;
}

MATRIZ Madj(MATRIZ a)//Matriz adjunta de a, probada en 3x3
{
    int i,j;
    MATRIZ c=Minit(a.dim[0],a.dim[1]);
    c=Zeros(c);
    for(i=0;i<a.dim[0];i++)
    {
        for(j=0;j<a.dim[1];j++)
        {
            c.p[i][j]=(pow(-1,i+j)*Mdet(Mcof(a,i,j)));
        }
    }

    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return c;

}

MATRIZ Mtrans(MATRIZ a)
{
    int i,j;
    MATRIZ c=Minit(a.dim[1],a.dim[0]);
    c=Zeros(c);
    for(i=0;i<c.dim[0];i++)
    {
        for(j=0;j<c.dim[1];j++)
        {
            c.p[i][j]=a.p[j][i];
        }
    }
    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }
    return c;

}
MATRIZ Minv(MATRIZ a)
{

    int i,j,k,l;
    float s,t;
    MATRIZ b=Meye(a.dim[0]);
    if (Mdet(a)==0)
    {
        UART_OutString("Minv error");
        return error;
    }

    for (j=0;j<a.dim[0];j++)
    {
        for(i=j;i<a.dim[0];i++)
        {
            if(a.p[i][j]!=0)
            {
                for(k=0;k<a.dim[0];k++)
                {
                    s=a.p[j][k];
                    a.p[j][k]=a.p[i][k];
                    a.p[i][k]=s;

                    s=b.p[j][k];
                    b.p[j][k]=b.p[i][k];
                    b.p[i][k]=s;

                }
                t=1/a.p[j][j];
                for(k=0;k<a.dim[0];k++)
                {
                    a.p[j][k]=t*a.p[j][k];
                    b.p[j][k]=t*b.p[j][k];
                }
                for(l=0;l<a.dim[0];l++)
                {
                    if(l!=j)
                    {
                        t=-a.p[l][j];
                        for(k=0;k<a.dim[0];k++)
                        {
                            a.p[l][k]=a.p[l][k]+t*a.p[j][k];
                            b.p[l][k]=b.p[l][k]+t*b.p[j][k];
                        }

                    }
                }
            }
            break;
        }
        if( a.p[i][j]==0)
        {
            UART_OutString("Minv \t");
            return error;
        }


    }

    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }


    return b;

}


MATRIZ Mcrz(MATRIZ a,MATRIZ b)//producto cruz de forma matricial.
{
    MATRIZ c=Minit(3,1);
    c.p[0][0]=a.p[1][0]*b.p[2][0]-a.p[2][0]*b.p[1][0];
    c.p[1][0]=a.p[0][0]*b.p[2][0]-a.p[2][0]*b.p[0][0];
    c.p[2][0]=a.p[0][0]*b.p[1][0]-a.p[1][0]*b.p[0][0];
    return c;

}

float Mtraza(MATRIZ a)
{
    float b=0;
    int i;
    for(i=0;i<a.dim[0];i++)
    {
        b+=a.p[i][i];
    }

    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return b;
}

MATRIZ vec2m(VECTOR a)
{
    MATRIZ c=Minit(1,a.dim);
    int i;
    if (c.p==NULL)
    {
        UART_OutString("vec2m \t");
        return error;

    }

    for(i=0;i<a.dim;i++)
    {
        c.p[0][i]=a.p[i];
    }


    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return c;

}
VECTOR m2vec(MATRIZ a)
{
    VECTOR c=Vinit(a.dim[1]);
    int i;
    for(i=0;i<c.dim;i++)
    {
        c.p[i]=a.p[0][i];
    }


    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return c;
}
QUAT m2q(MATRIZ a)
{
    QUAT cuat={0,0};
    int i;
    for( i=0;i<a.dim[1];i++)
    {
        cuat.q[i]=a.p[0][i];
    }

    if(a.willFree==0)
    {
        //free(a.p);
        //memoria-=1;
    }

    return cuat;
}



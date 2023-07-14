/*
 * kalman2.c
 *
 *  Created on: 16 ene 2023
 *      Author: rober
 */


#include<stdio.h>
#include<stdint.h>
#include<math.h>
#include"structs.h"
#include"vector.h"
#include"matrix.h"
#include"cuaternion.h"
#include"rotacion.h"
#include"kalman2.h"
#include"UART.h"

int max(QUAT q);
int index(int i,int indice);

kalman_data2 kalman_Init2()
{

    kalman_data2 kd;
    float x[6][1]={{0.3*0.3},{0.3*0.3},{0.3*0.3},{0.5*0.5},{0.5*0.5},{0.5*0.5}};
    kd.x_n=MinitZ(6,1);
    kd.x_n=Masign(kd.x_n,&x[0][0]);

    //float p[7]={0.1*0.1, 0.1*0.1, 0.1*0.1, 0.1*0.1, pow(0.1*PI/180,2), pow(0.1*PI/180,2), pow(0.1*PI/180,2)};
    float p_n[6][6]={{0.1*0.1, 0      , 0      , 0                , 0                , 0         },
                     {0      , 0.1*0.1, 0      , 0                , 0                , 0         },
                     {0      , 0      , 0.1*0.1, 0                , 0                , 0         },
                     {0      , 0      , 0      , pow(0.5,2)       , 0                , 0         },
                     {0      , 0      , 0      , 0                , pow(0.5,2)       , 0         },
                     {0      , 0      , 0      , 0                , 0                , pow(0.5,2)}};
    kd.P_n=MinitZ(7,7);
    kd.P_n=Masign(kd.P_n,&p_n[0][0]);

    kd.x_es=MinitZ(7,1);
    kd.P_es=MinitZ(7,7);


    kd.R=MinitZ(6,6);
    float r[6][6]={{0.25   , 0      , 0      , 0                , 0                , 0         },
                   {0      , 0.25   , 0      , 0                , 0                , 0         },
                   {0      , 0      , 0.25   , 0                , 0                , 0         },
                   {0      , 0      , 0      , 0.015            , 0                , 0         },
                   {0      , 0      , 0      , 0                , 0.015            , 0         },
                   {0      , 0      , 0      , 0                , 0                , 0.015     }};
    kd.R=Masign(kd.R,&r[0][0]);

    return kd;


}



kalman_data pred_EKF(kalman_data kd, kalman_data kdn, float dt, VECTOR gyro, MATRIZ N)
{
    return kd;
}



kalman_data correc_EKF(kalman_data kp,kalman_data kdn, MATRIZ R, VECTOR med, VECTOR ref, MATRIZ rot)
{
    return kp;
}



kalman_data2 EKF2(kalman_data2 kd, kalman_data2 kdn, MATRIZ A,  VECTOR gyro, VECTOR medMag, VECTOR medSol, VECTOR refMag, VECTOR refSol, float dt)
{
    int i,j;
    A=Mtrans(A);
    QUAT qx;
    qx.q[0]=kd.x_n.p[0][0];
    qx.q[1]=kd.x_n.p[1][0];
    qx.q[2]=kd.x_n.p[2][0];
    qx.q[3]=kd.x_n.p[3][0];
    MATRIZ Ar=c2rot((Cnorm(qx)));
    MATRIZ It=MinitZ(3,3);
    It.p[0][0]=0.0017;
    It.p[1][1]=0.0015;
    It.p[2][2]=0.002;

    float alfa=(It.p[1][1]-It.p[2][2])/It.p[0][0];
    float beta=(It.p[2][2]-It.p[1][1])/It.p[1][1];
    float gama=(It.p[0][0]-It.p[0][0])/It.p[2][2];


    float q1=kd.x_n.p[0][0];
    float q2=kd.x_n.p[1][0];
    float q3=kd.x_n.p[2][0];
    float q4=kd.x_n.p[3][0];
    float wx=kd.x_n.p[4][0];
    float wy=kd.x_n.p[5][0];
    float wz=kd.x_n.p[6][0];

    MATRIZ qxm=MinitZ(4,1);
    qxm.p[0][0]=qx.q[0];
    qxm.p[1][0]=qx.q[1];
    qxm.p[2][0]=qx.q[2];
    qxm.p[3][0]=qx.q[3];

    MATRIZ w=MinitZ(3,1);
    w.p[0][0]=wx;
    w.p[1][0]=wy;
    w.p[2][0]=wz;

    MATRIZ Omega=Minit(4,4);
    float omega[4][4]={{0, wz, -wy, wx},{-wz, 0, wx, wy},{wy, -wx, 0, wz},{-wx, -wy, -wz, 0}};

    Omega=Masign(Omega,&omega[0][0]);


    MATRIZ Xi=Minit(4,3);
    float xi[4][3]={{q4, -q3, q2},{q3, q4, -q1},{-q2, q1, q4},{-q1,-q2,-q3}};
    Xi=Masign(Xi,&xi[0][0]);

    MATRIZ Pi=Minit(3,4);
    float pi[3][4]={{0, alfa*wz, alfa*wy},{beta*wz, 0 , beta*wx},{gama*wy, gama*wx, 0}};
    Pi=Masign(Pi,&pi[0][0]);

    int indice=max(qx);
    /////////////Matrices truncadas

    MATRIZ OmegaTrunc=Minit(3,3);
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            OmegaTrunc.p[i][j]=Omega.p[index(i,indice)][index(j,indice)]-qx.q[index(j,indice)]/qx.q[indice]*Omega.p[index(i,indice)][indice];
        }
    }

    MATRIZ XiTrunc=Minit(3,3);
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            XiTrunc.p[i][j]=Xi.p[index(i,indice)][j];
        }
    }
    MATRIZ F11T=Mmules(1/2,OmegaTrunc);
    MATRIZ F12T=Mmules(1/2,XiTrunc);
    MATRIZ F21T=MinitZ(3,3);
    MATRIZ F22T=Pi;

    MATRIZ Ftrunc=Minit(6,6);

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Ftrunc.p[i][j]=F11T.p[i][j];
            Ftrunc.p[i][3+j]=F12T.p[i][j];
            Ftrunc.p[3+i][j]=F21T.p[i][j];
            Ftrunc.p[3+i][3+j]=F22T.p[i][j];

        }
    }
    MATRIZ h1=Mmules(1/Vmod(medMag),Mmul(Mtrans(A),vec2m(medMag)));
    MATRIZ h2=Mmules(1/Vmod(medSol),Mmul(Mtrans(A),vec2m(medSol)));
    MATRIZ H=Minit(6,1);/////////////QUE DIMENSION ES ESTA SECCION
    for(i=0;i<3;i++)
    {

        H.p[i][0]=h1.p[i][0];
        H.p[i+3][0]=h2.p[i][0];

    }

    MATRIZ h1es=Mmules(1/Vmod(refMag),Mmul(Mtrans(A),vec2m(refMag)));
    MATRIZ h2es=Mmules(1/Vmod(refSol),Mmul(Mtrans(A),vec2m(refSol)));
    MATRIZ Hes=Minit(6,1);/////////////QUE DIMENSION ES ESTA SECCION
    for(i=0;i<3;i++)
    {

        Hes.p[i][0]=h1es.p[i][0];
        Hes.p[i+3][0]=h2es.p[i][0];

    }
    MATRIZ y=Mres(H,Hes);

    MATRIZ parAq1=Minit(3,3);
    float par1[3][3]={{2*q1,2*q2, 2*q3 },{2*q2, -2*q1, 2*q4},{2*q3, -2*q4, -2*q1}};
    parAq1=Masign(parAq1,&par1[0][0]);


    MATRIZ parAq2=Minit(3,3);
    float par2[3][3]={{-2*q2, 2*q1, -2*q4 },{2*q1, 2*q2, 2*q3},{2*q4, 2*q3, -2*q2}};
    parAq2=Masign(parAq2,&par2[0][0]);

    MATRIZ parAq3=Minit(3,3);
    float par3[3][3]={{-2*q3, 2*q4, 2*q1 },{-2*q4, -2*q3, 2*q2},{2*q1, 2*q2, 2*q3}};
    parAq3=Masign(parAq3,&par3[0][0]);

    MATRIZ parAq4=Minit(3,3);
    float par4[3][3]={{2*q4, 2*q3, -2*q2 },{-2*q3, 2*q4, 2*q1},{2*q2, -2*q1, 2*q4}};
    parAq4=Masign(parAq4,&par4[0][0]);


    MATRIZ theta11=Mmul(parAq1,Mmules(1/Vmod(medMag),vec2m(medMag)));
    MATRIZ theta12=Mmul(parAq2,Mmules(1/Vmod(medMag),vec2m(medMag)));
    MATRIZ theta13=Mmul(parAq3,Mmules(1/Vmod(medMag),vec2m(medMag)));
    MATRIZ theta14=Mmul(parAq4,Mmules(1/Vmod(medMag),vec2m(medMag)));

    MATRIZ theta21=Mmul(parAq1,Mmules(1/Vmod(medSol),vec2m(medSol)));
    MATRIZ theta22=Mmul(parAq2,Mmules(1/Vmod(medSol),vec2m(medSol)));
    MATRIZ theta23=Mmul(parAq3,Mmules(1/Vmod(medSol),vec2m(medSol)));
    MATRIZ theta24=Mmul(parAq4,Mmules(1/Vmod(medSol),vec2m(medSol)));

    MATRIZ Theta=Minit(6,4);
    for (i=0;i<3;i++);
    {
        Theta.p[i][0]=theta11.p[i][0];
        Theta.p[i][1]=theta12.p[i][0];
        Theta.p[i][2]=theta13.p[i][0];
        Theta.p[i][3]=theta14.p[i][0];

        Theta.p[i+3][0]=theta21.p[i][0];
        Theta.p[i+3][1]=theta22.p[i][0];
        Theta.p[i+3][2]=theta23.p[i][0];
        Theta.p[i+3][3]=theta24.p[i][0];

    }

    MATRIZ ThetaTrunc=Minit(6,3);

    for(i=0;i<6;i++)
    {
        for(j=0;j<3;j++)
        {
            ThetaTrunc.p[i][j]=Theta.p[i][index(j,indice)]-(qx.q[index(j,indice)]/qx.q[indice])*Theta.p[i][indice];
        }
    }

    MATRIZ Htrunc=MinitZ(6,6);
    for(i=0;i<6;i++)
    {
        for(j=0;j<3;j++)
        {
            Htrunc.p[i][j]=ThetaTrunc.p[i][j];
        }
    }

    MATRIZ S=MinitZ(3,3);
    S.p[0][0]=0.001;
    S.p[1][1]=0.001;
    S.p[2][2]=0.001;

    MATRIZ Q1=MinitZ(6,6);
    Q1.p[3][3]=It.p[0][0];
    Q1.p[4][4]=It.p[1][1];
    Q1.p[5][5]=It.p[2][2];

    MATRIZ Q2=MinitZ(6,6);
    MATRIZ Qt=Mmul(F12T,S);

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q2.p[i][j+3]=Qt.p[i][j];
        }
    }
    Qt=Mtrans(Mmul(Mtrans(F21T),S));
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q2.p[i+3][j]=Qt.p[i][j];
        }
    }
    Qt=Msum(Mmul(Mtrans(F22T),S),Mmul(F22T,S));
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q2.p[i+3][j+3]=Qt.p[i][j];
        }
    }

    MATRIZ Q3=MinitZ(6,6);
    Qt=Mmul(Mmul(F12T,S),Mtrans(F12T));
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q3.p[i][j]=Qt.p[i][j];
        }
    }

    Qt=Mmul(Mmul(F12T,S),Mtrans(F22T));
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q3.p[i][j+3]=Qt.p[i][j];
        }
    }

    Qt=Mmul(Mmul(F22T,S),Mtrans(F12T));
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q3.p[i+3][j]=Qt.p[i][j];
        }
    }

    Qt=Mmul(Mmul(F22T,S),Mtrans(F22T));

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q3.p[i+3][j+3]=Qt.p[i][j];
        }
    }
    MATRIZ tau=MinitZ(0,0);

    MATRIZ Q=Msum(Msum(Mmules(dt,Q1),Mmules((dt*dt)/2,Q2)),Mmules((dt*dt*dt)/3,Q3));


    //ESTIMACION

    MATRIZ qest=Mmules(1/2,Mmul(Omega,qxm));
    MATRIZ west=Mmul(Minv(It),Mres(tau,Mcrz(w,Mmul(It,w))));
    MATRIZ xesT=MinitZ(6,1);
    MATRIZ qestT=MinitZ(1,3);
    for(i=0;i<3;i++)
    {
        qestT.p[i][0]=qest.p[index(i,indice)][0];
    }
    for(i=0;i<3;i++)
    {
        xesT.p[i][0]=qestT.p[i][0];
        xesT.p[i+3][0]=west.p[i][0];
    }
    kd.P_es=Msum(Msum(Mmul(Ftrunc,kd.P_n),Mmul(kd.P_n,Mtrans(Ftrunc))),Qt);

    //CORRECCION

    MATRIZ KT=Mmul(Mmul(kd.P_es,Mtrans(Htrunc)),Minv(Msum(kdn.R,Mmul(Mmul(Htrunc,kd.P_es),Mtrans(Htrunc)))));
    MATRIZ x_nT=Msum(xesT,Mmul(KT,y));
    kdn.P_n=Mmul(Mres(Mmules(0.001,Meye(6)),Mmul(KT,Htrunc)),kdn.P_es);

    for(i=0;i<3;i++)
    {
        kdn.x_n.p[index(i,indice)][0]=x_nT.p[i][0]/sqrt(pow(qest.p[indice][0],2)+pow(x_nT.p[0][0],2)+pow(x_nT.p[1][0],2)+pow(x_nT.p[2][0],2));
    }
    kdn.x_n.p[indice][0]=qest.p[indice][0]/sqrt(pow(qest.p[indice][0],2)+pow(x_nT.p[0][0],2)+pow(x_nT.p[1][0],2)+pow(x_nT.p[2][0],2));
    for(i=0;i<3;i++)
    {
        kdn.x_n.p[i+4][0]=x_nT.p[i+3][0];
    }
    return kdn;









}

int index(int i,int indice)
{
    if(i<indice)
        return i;
    else
        return i+1;
}

int max(QUAT q)
{
    if(q.q[0]>=q.q[1])
    {
        if(q.q[0]>=q.q[2])
        {
            if(q.q[0]>=q.q[3])
            {
                return 0;
            }
            else
            {
                return 3;
            }
        }
        else
        {
            if(q.q[2]>=q.q[3])
            {
                return 2;
            }
            else
            {
                return 3;
            }
        }
    }
    else
    {
        if(q.q[1]>=q.q[2])
        {
            if(q.q[1]>=q.q[3])
            {
                return 1;
            }
            else
            {
                return 3;
            }
        }
        else
        {
            if(q.q[2]>=q.q[3])
            {
                return 2;
            }
            else
            {
                return 3;
            }
        }
    }
}





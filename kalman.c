/*
 * kalman.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */
#include<stdio.h>
#include<stdint.h>
#include<math.h>
#include"structs.h"
#include"vector.h"
#include"matrix.h"
#include"cuaternion.h"
#include"kalman.h"
#include"UART.h"

float m1[3][3];
float m2[3][3];
float m3[3][3];
float m4[3][3];
/*
MATRIZ Omega;
MATRIZ I;
MATRIZ wb;*/

kalman_data kalmanInit()
{
    kalman_data kd;
    float x[7][1]={{0.3*0.3},{0.3*0.3},{0.3*0.3},{0.3*0.3},{0.5*0.5},{0.5*0.5},{0.5*0.5}};
    kd.x_n=MinitZ(7,1);
    kd.x_n=Masign(kd.x_n,&x[0][0]);

    //float p[7]={0.1*0.1, 0.1*0.1, 0.1*0.1, 0.1*0.1, pow(0.1*PI/180,2), pow(0.1*PI/180,2), pow(0.1*PI/180,2)};
    float p_n[7][7]={{0.1*0.1, 0      , 0      , 0      , 0                , 0                , 0         },
                     {0      , 0.1*0.1, 0      , 0      , 0                , 0                , 0         },
                     {0      , 0      , 0.1*0.1, 0      , 0                , 0                , 0         },
                     {0      , 0      , 0      , 0.1*0.1, 0                , 0                , 0         },
                     {0      , 0      , 0      , 0      , pow(0.5,2)       , 0                , 0         },
                     {0      , 0      , 0      , 0      , 0                , pow(0.5,2)       , 0         },
                     {0      , 0      , 0      , 0      , 0                , 0                , pow(0.5,2)}};
    kd.P_n=MinitZ(7,7);
    kd.P_n=Masign(kd.P_n,&p_n[0][0]);

    kd.x_es=MinitZ(7,1);
    kd.P_es=MinitZ(7,7);
    kd.H=MinitZ(3,7);
    kd.I=MinitZ(3,3);
    kd.wb=MinitZ(3,1);
    kd.Omega=MinitZ(4,4);
    return kd;


}


kalman_data predEKF(kalman_data kd, kalman_data kdn, float dt, VECTOR gyro, MATRIZ N)
{
    MATRIZ qa=MinitZ(4,1);

    MATRIZ wa=MinitZ(3,1);

    qa.p[0][0]=kd.x_n.p[0][0];
    qa.p[1][0]=kd.x_n.p[1][0];
    qa.p[2][0]=kd.x_n.p[2][0];
    qa.p[3][0]=kd.x_n.p[3][0];
    wa.p[0][0]=kd.x_n.p[4][0];
    wa.p[1][0]=kd.x_n.p[5][0];
    wa.p[2][0]=kd.x_n.p[6][0];

    kdn.P_es=Msum(Mmul(Mmul(kdn.Fi,kd.P_n),Mtrans(kdn.Fi)),kdn.Q);
    qa=Msum(qa,Mmules(dt,Mmul(kdn.Omega,qa)));
    wa=Msum(wa,Mmules(dt,Mmul(Minv(kdn.I),Mres(N,Mcrz(kdn.wb,Mmul(kdn.I,kdn.wb))))));

    kdn.x_es.p[0][0]=qa.p[0][0];
    kdn.x_es.p[1][0]=qa.p[1][0];
    kdn.x_es.p[2][0]=qa.p[2][0];
    kdn.x_es.p[3][0]=qa.p[3][0];
    kdn.x_es.p[4][0]=gyro.p[0];
    kdn.x_es.p[5][0]=gyro.p[1];
    kdn.x_es.p[6][0]=gyro.p[2];
    return kdn;
}

kalman_data correcEKF(kalman_data kp, kalman_data kdn, MATRIZ R, VECTOR med, VECTOR ref, MATRIZ rot)
{
    int i,j;
    //Matriz de observación

    MATRIZ M1=MinitZ(3,3);
    M1=Masign(M1,&m1[0][0]);
    MATRIZ M2=MinitZ(3,3);
    M2=Masign(M2,&m2[0][0]);
    MATRIZ M3=MinitZ(3,3);
    M3=Masign(M3,&m3[0][0]);
    MATRIZ M4=MinitZ(3,3);
    M4=Masign(M4,&m4[0][0]);
/*
    M1=Mmul(Mmules(2,M1),Mtrans(vec2m(med)));
    M2=Mmul(Mmules(2,M2),Mtrans(vec2m(med)));
    M3=Mmul(Mmules(2,M3),Mtrans(vec2m(med)));
    M4=Mmul(Mmules(2,M4),Mtrans(vec2m(med)));*/

    M1=Mmul(Mmules(2,M1),Mtrans(vec2m(ref)));
    M2=Mmul(Mmules(2,M2),Mtrans(vec2m(ref)));
    M3=Mmul(Mmules(2,M3),Mtrans(vec2m(ref)));
    M4=Mmul(Mmules(2,M4),Mtrans(vec2m(ref)));

    //kp.H=Minit(3,7);
    for(i=0;i<3;i++)
    {
        kdn.H.p[i][0]=M1.p[i][0];
        kdn.H.p[i][1]=M2.p[i][0];
        kdn.H.p[i][2]=M3.p[i][0];
        kdn.H.p[i][3]=M4.p[i][0];
        for( j=0;j<3;j++)
        {
            kdn.H.p[i][j+4]=0;
        }
    }

    //Matriz de ganancia
    if (Mdet(Msum(Mmul(Mmul(kdn.H,kdn.P_n),Mtrans(kdn.H)),R))==0)
    {
        UART_OutString("K error");

    }

    //UART_OutUFloat(Mdet(Msum(Mmul(Mmul(kdn.H,kdn.P_n),Mtrans(kdn.H)),R)),7);
    //UART_OutString("|||||\t");

    kdn.K=Mmul(Mmul(kdn.P_es,Mtrans(kdn.H)),Minv(Msum(Mmul(Mmul(kdn.H,kdn.P_es),Mtrans(kdn.H)),R)));
    if(kdn.K.dim[0]==0 && kdn.K.dim[1]==0)
    {
        kdn.K=kp.K;
    }
    MATRIZ I=Meye(7);
    //I.p[4][4]=kdn.I.p[0][0];
    //I.p[5][5]=kdn.I.p[1][1];
    //I.p[6][6]=kdn.I.p[2][2];

    kdn.x_n=Msum(kdn.x_n,Mmul(kdn.K,Mres(Mtrans(vec2m(med)),Mmul(rot,Mtrans(vec2m(ref))))));
    kdn.P_n=Mmul(Mres(I,Mmul(kdn.K,kdn.H)),kdn.P_n);
    QUAT q;
    q.q[0]=kdn.x_n.p[0][0];
    q.q[1]=kdn.x_n.p[1][0];
    q.q[2]=kdn.x_n.p[2][0];
    q.q[3]=kdn.x_n.p[2][0];

    q=Cnorm(q);

    kdn.x_n.p[0][0]=q.q[0];
    kdn.x_n.p[1][0]=q.q[1];
    kdn.x_n.p[2][0]=q.q[2];
    kdn.x_n.p[3][0]=q.q[3];


    return kdn;
}
kalman_data EKF(kalman_data kd, kalman_data kdn, MATRIZ A, VECTOR gyro, float dt)
{
    /*Calcula la matriz de transición de estados, siendo esta el jacobiano de las ecuaciones del sistema
     *
     *
     *
     */
    //Declaracion de variables
    float Ix = 159.2;//Momentos de inercia
    float Iy = 158.2;
    float Iz = 4.91;


    float wx=kd.x_n.p[4][0];
    float wy=kd.x_n.p[5][0];
    float wz=kd.x_n.p[6][0];
/*
    float wx=gyro.p[0];
    float wy=gyro.p[1];
    float wz=gyro.p[2];
*/
    float hx=0;
    float hy=0;
    float hz=0;

    float alfa=(Iz-Iy)/Ix;
    float beta=(Ix-Iz)/Iy;
    float gama=(Iy-Ix)/Iz;

    float wox=1;
    float woy=1;
    float woz=1;

    VECTOR w=Vinit(3);
    w.p[0]=0;
    w.p[1]=0;
    w.p[2]=0;

    VECTOR N=Vinit(3);
    N.p[0]=0;
    N.p[1]=0;
    N.p[2]=0;

    //MATRIZ I=MinitZ(3,3);
    kdn.I.p[0][0]=Ix;
    kdn.I.p[1][1]=Iy;
    kdn.I.p[2][2]=Iz;

    VECTOR h=Vinit(3);
    h.p[0]=0;
    h.p[1]=0;
    h.p[2]=0;

    //VECTOR wb=Vinit(3);
    kdn.wb.p[0][0]=wx;
    kdn.wb.p[1][0]=wy;
    kdn.wb.p[2][0]=wz;

    /*VECTOR wlo=Vinit(3);
    wlo.p[0]=wox;
    wlo.p[1]=woy;
    wlo.p[2]=woz;*/
    VECTOR wlo=m2vec(Mtrans(Mmul(Minv(A),kdn.wb)));
    wox=wlo.p[0];
    woy=wlo.p[1];
    woz=wlo.p[2];

    float w0=0.0010924576567;//periodo orbital rad/seg


    float Om[4][4]={{0, woz,-woy, wox},{-woz,0,wox,woy},{woy, -wox, 0, woz},{-wox,-woy,-woz,0}};
    //MATRIZ Omega=Minit(4,4);
    kdn.Omega=Masign(kdn.Omega,&Om[0][0]);

    float f11[4][4]={{kd.x_n.p[2][0]*kd.x_n.p[0][0], kd.x_n.p[0][0]*kd.x_n.p[3][0], 1-(kd.x_n.p[0][0]*kd.x_n.p[0][0]), -kd.x_n.p[0][0]*kd.x_n.p[1][0]},
                     {kd.x_n.p[2][0]*kd.x_n.p[1][0], kd.x_n.p[1][0]*kd.x_n.p[3][0], -kd.x_n.p[0][0]*kd.x_n.p[1][0], 1-(kd.x_n.p[1][0]*kd.x_n.p[1][0])},
                     {(kd.x_n.p[2][0]*kd.x_n.p[2][0])-1, kd.x_n.p[2][0]*kd.x_n.p[3][0], -kd.x_n.p[0][0]*kd.x_n.p[2][0], -kd.x_n.p[1][0]*kd.x_n.p[2][0]},
                     {kd.x_n.p[2][0]*kd.x_n.p[3][0], (kd.x_n.p[3][0]*kd.x_n.p[3][0])-1, -kd.x_n.p[0][0]*kd.x_n.p[3][0], -kd.x_n.p[1][0]*kd.x_n.p[3][0]}};
    MATRIZ F11=MinitZ(4,4);
    F11=Masign(F11,&f11[0][0]);
    F11=Msum(Mmules(1/2,kdn.Omega),Mmules(w0,F11));

    float f12[4][3]={{kd.x_n.p[3][0], -kd.x_n.p[2][0], kd.x_n.p[1][0]},
                     {kd.x_n.p[2][0], kd.x_n.p[3][0], -kd.x_n.p[0][0]},
                     {-kd.x_n.p[1][0], kd.x_n.p[0][0], kd.x_n.p[3][0]},
                     {-kd.x_n.p[0][0], -kd.x_n.p[1][0], -kd.x_n.p[2][0]}};
    MATRIZ F12=MinitZ(4,3);
    F12=Masign(F12,&f12[0][0]);
    F12=Mmules(1/2,F12);

    float f21[3][4]={{alfa*(-A.p[1][2]*kd.x_n.p[0][0] + A.p[2][2]*kd.x_n.p[3][0]), alfa*(-A.p[1][2]*kd.x_n.p[1][0] + A.p[2][2]*kd.x_n.p[2][0]), alfa*(A.p[1][2]*kd.x_n.p[2][0] + A.p[2][2]*kd.x_n.p[1][0]), alfa*(A.p[1][2]*kd.x_n.p[3][0] + A.p[2][2]*kd.x_n.p[0][0])},
                     {beta*(A.p[2][2]*kd.x_n.p[2][0] - A.p[0][2]*kd.x_n.p[0][0]), beta*(-A.p[2][2]*kd.x_n.p[3][0] - A.p[0][2]*kd.x_n.p[1][0]), beta*(A.p[2][2]*kd.x_n.p[0][0] + A.p[0][2]*kd.x_n.p[2][0]), beta*(-A.p[2][2]*kd.x_n.p[1][0] + A.p[0][2]*kd.x_n.p[3][0])},
                     {gama*(A.p[0][2]*kd.x_n.p[3][0] + A.p[1][2]*kd.x_n.p[2][0]), gama*(A.p[0][2]*kd.x_n.p[2][0] - A.p[1][2]*kd.x_n.p[3][0]), gama*(A.p[0][2]*kd.x_n.p[1][0] + A.p[1][2]*kd.x_n.p[0][0]), gama*(A.p[0][2]*kd.x_n.p[0][0] - A.p[1][2]*kd.x_n.p[1][0])}};
    MATRIZ F21=MinitZ(3,4);
    F21=Masign(F21,&f21[0][0]);
    F21=Mmules(6*w0*w0,F21);

    float f22[3][3]={{0             , -alfa*wz-hz/Ix, -alfa*wy+hy/Ix},
                     {-beta*wz+hz/Iy, 0             , -beta*wx-hx/Iy},
                     {-gama*wy-hy/Iz, -gama*wx+hx/Iz, 0}};
    MATRIZ F22=MinitZ(3,3);
    F22=Masign(F22,&f22[0][0]);

    MATRIZ F=MinitZ(7,7);
    //kd.Fi=Minit(7,7);
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            F.p[i][j]=F11.p[i][j];
        }
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
        {
            F.p[i][j+4]=F12.p[i][j];
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            F.p[i+4][j]=F21.p[i][j];
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            F.p[i+4][j+4]=F22.p[i][j];
        }
    }

    kdn.Fi=Msum(Meye(7),Mmules(dt,F));

    ///////////////
    float sigma[3]={0.00510,0.00510,0.00510};//{sigmax, sigmay, sigmaz} desviaciones estandar de las mediaciones

    MATRIZ S=MinitZ(3,3);
    for(i=0;i<3;i++)
    {
        S.p[i][i]=sigma[i];
    }
    MATRIZ Q1=MinitZ(7,7);
    for(i=0;i<3;i++)
    {
        Q1.p[i+4][i+4]=sigma[i];
    }

    MATRIZ Q2=MinitZ(7,7);
    MATRIZ Q212=Mmul(F12,S);
    MATRIZ Q221=Mtrans(Mmul(F12,S));
    MATRIZ Q222=Msum(Mmul(Mtrans(F22),S),Mmul(F22,S));

    for (i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
        {
            Q2.p[i][j+4]=Q212.p[i][j];
        }
    }
    for (i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            Q2.p[i+4][j]=Q221.p[i][j];
        }
    }
    for (i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q2.p[i+4][j+4]=Q222.p[i][j];
        }
    }

    MATRIZ Q311=Mmul(Mmul(F12,S),Mtrans(F12));
    MATRIZ Q312=Mmul(Mmul(F12,S),Mtrans(F22));
    MATRIZ Q321=Mmul(Mmul(F22,S),Mtrans(F12));
    MATRIZ Q322=Mmul(Mmul(F22,S),Mtrans(F22));
    MATRIZ Q3=MinitZ(7,7);

    for (i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            Q3.p[i][j]=Q311.p[i][j];
        }
    }

    for (i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
        {
            Q3.p[i][j+4]=Q312.p[i][j];
        }
    }
    for (i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            Q3.p[i+4][j]=Q321.p[i][j];
        }
    }
    for (i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            Q3.p[i+4][j+4]=Q322.p[i][j];
        }
    }

    //kd.Q=Msum(Msum(Mmules(dt,Q1),Mmules((dt*dt)/2,Q2)),Mmules((dt*dt*dt)/3),Q3);
    kdn.Q=Msum(Msum(Mmules(dt,Q1),Mmules(dt*dt/2,Q2)),Mmules(dt*dt*dt/3,Q3));
    //Matriz de observación

    /*m1={{q.q[0], q.q[1], q.q[2]},
                  {q.q[1], -q.q[0], q.q[3]},
                  {q.q[2], -q.q[3], -q.q[0]}};*/
    m1[0][0]=kd.x_n.p[0][0]*2;
    m1[0][1]=kd.x_n.p[1][0]*2;
    m1[0][2]=kd.x_n.p[2][0]*2;
    m1[1][0]=kd.x_n.p[1][0]*2;
    m1[1][1]=-kd.x_n.p[0][0]*2;
    m1[1][2]=kd.x_n.p[3][0]*2;
    m1[2][0]=kd.x_n.p[2][0]*2;
    m1[2][1]=-kd.x_n.p[3][0]*2;
    m1[2][2]=-kd.x_n.p[0][0]*2;
    /*m2={{-q.q[1], q.q[0], -q.q[3]},
                  {q.q[0], q.q[1], q.q[2]},
                  {q.q[3], q.q[2], -q.q[1]}};*/

    m2[0][0]=-kd.x_n.p[1][0]*2;
    m2[0][1]=kd.x_n.p[0][0]*2;
    m2[0][2]=-kd.x_n.p[3][0]*2;
    m2[1][0]=kd.x_n.p[0][0]*2;
    m2[1][1]=kd.x_n.p[1][0]*2;
    m2[1][2]=kd.x_n.p[2][0]*2;
    m2[2][0]=kd.x_n.p[3][0]*2;
    m2[2][1]=kd.x_n.p[2][0]*2;
    m2[2][2]=-kd.x_n.p[1][0]*2;
    /*m3={{-q.q[2], q.q[3], q.q[0]},
                  {-q.q[3], -q.q[2], q.q[1]},
                  {q.q[0], q.q[1], q.q[2]}};*/
    m3[0][0]=-kd.x_n.p[2][0]*2;
    m3[0][1]=kd.x_n.p[3][0]*2;
    m3[0][2]=kd.x_n.p[0][0]*2;
    m3[1][0]=-kd.x_n.p[3][0]*2;
    m3[1][1]=-kd.x_n.p[2][0]*2;
    m3[1][2]=kd.x_n.p[1][0]*2;
    m3[2][0]=kd.x_n.p[0][0]*2;
    m3[2][1]=kd.x_n.p[1][0]*2;
    m3[2][2]=kd.x_n.p[2][0]*2;
    /*m4={{q.q[3], q.q[2], -q.q[1]},
                  {-q.q[2], q.q[3], q.q[0]},
                  {q.q[1], -q.q[0], q.q[3]}};*/
    m4[0][0]=kd.x_n.p[3][0]*2;
    m4[0][1]=kd.x_n.p[2][0]*2;
    m4[0][2]=-kd.x_n.p[1][0]*2;
    m4[1][0]=-kd.x_n.p[2][0]*2;
    m4[1][1]=kd.x_n.p[3][0]*2;
    m4[1][2]=kd.x_n.p[0][0]*2;
    m4[2][0]=kd.x_n.p[1][0]*2;
    m4[2][1]=-kd.x_n.p[0][0]*2;
    m4[2][2]=kd.x_n.p[3][0]*2;

    return kdn;





}



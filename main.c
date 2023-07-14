#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
//#include "tm4c1294ncpdt.h"
#include "tm4c.h"
#include "structs.h"
#include "vector.h"
#include "matrix.h"
#include "rotacion.h"
#include "cuaternion.h"
#include "estimadores.h"
#include "IGRF.h"
#include "adc.h"

#include "wire.h"

#include "L3GD20H.h"
#include "HMC5883L.h"
#include "DS3231.h"
#include "wire.h"
#include "lecturas.h"
#include "lcd.h"
#include "kalman.h"
#include "UART.h"

//variables globales

int memoria=0;
uint8_t err;

//void UART0_Init(void);
//void txchar(char c);
kalman_data ADCS(kalman_data kd);
int main(void)
{
    int vuelta=0;

    time_stat timenow;
    time_stat timepas;
    timenow.seconds=00;
    timenow.minutes=2;
    timenow.hour=11;
    timenow.day=1;
    timenow.date=31;
    timenow.month=1;
    timenow.year=23;


    uint32_t v[6],A[6],T[6],p[6];
    uint8_t raw_data[6];
    short data[3];
    float MagField[3];
    char dataChr[3];

    //float v[6],A[6],T[6];
    //float *av,Vm[6]={0.8,0.9,0.8,0.1,0.1,0};
    //float *ai,Im[6]={1.07,1.07,1.07,1.07,1.07,1.07};
    //float *at,t[6]={26,26,26,26,26,26};
    //av=Vm;
    //ai=Im;
    //at=t;
    PortL_Init();//Incluye el ADC
    //PortK_Init();//Muestra bits
    PortFunctionInit();//Activa puerto B, E, N, para LCD                               /* Initialize ports */
    GPIO_PORTN_DATA_R |= 0x01;
    CtlDelay(200000);                                        /* Give some delay */
    LCD_Clear();                                            /* Clear the LCD screen */
    LCD_OutString("ADS");                                    /* Write a string on the screen */
    CtlDelay(200000);                                      /* keep the string for some time on the screen */
    float conde=0;


    UART0_Init();

    ADC0_Init();
    I2C0_Init();
    err=esperar();
    int configHMC[3]={0x70,0x00,0x00};
    int configL3G1[6]={0x0F,0x00,0x00,0x30,0x10,0x00};
    int configL3G2[1]={0x00};
    configL3GD20H(&configL3G1[0]);//este es el bueno
    //configL3GD20H(LOW_ODR,&configL3G2[0],1);

    configHMC5883L(&configHMC[0],3);

    //configDS3231(&timenow);


    //VECTOR sol=lecturaSol(av,ai,at);
    //VECTOR angRate, estMag,vecSol,solEst;
    //VECTOR angRatea,estMaga,vecSola;
    float dt,angg=0;
    int dec,uni;
    float ang[3]={0,0,0};
    kalman_data kd=kalmanInit();


    //while(1)
    //{
        //int i;
        //readDS3231(&timenow);
        //dt=timenow.seconds-timepas.seconds;

//angRatea=lecturaGyro(&configL3G1[0]);
 //       estMag=lecturaMag(&configHMC[0]);
        /*readL3GD20H(&raw_data[0]);
        data[0]=(raw_data[0]+(raw_data[1]<<8));
        data[1]=(raw_data[2]+(raw_data[3]<<8));
        data[2]=(raw_
        data[4]+(raw_data[5]<<8));*/
//        lecturaADC(6,&v[0],&A[0],&T[0]);
  //      vecSol=lecturaSol(&v[0],&A[0],&T[0],&p[0]);
    //    solEst=estSol(timenow);
        //ADCS();

     //LCD_Clear();
        /*OutCmd(0x80);
        LCD_OutUFloat(estMag.p[0],4);
        LCD_OutString("  ");
        LCD_OutUFloat(estMag.p[1],4);
        OutCmd(0xC0);
        LCD_OutUFloat(estMag.p[2],4);
        LCD_OutString("  ");
        LCD_OutUFloat(sqrt(estMag.p[0]*estMag.p[0]+estMag.p[1]*estMag.p[1]+estMag.p[2]*estMag.p[2]),4);*/

//        OutCmd(0x80);

        /*LCD_OutUFloat(vecSol.p[0],4);
        LCD_OutString(" ");
        LCD_OutUFloat(vecSol.p[1],4);
        LCD_OutString(" ");
        OutCmd(0xC0);
        LCD_OutUFloat(vecSol.p[2],4);
        LCD_OutString(" ");
        LCD_OutUFloat(vecSol.status,3);*/

  /*      LCD_OutUFloat(estMag.p[0],4);
        LCD_OutString(" ");
        LCD_OutUFloat(estMag.p[1],4);
        LCD_OutString(" ");
        OutCmd(0xC0);

        LCD_OutUDec(timenow.hour);
        LCD_OutString(" ");
        LCD_OutUDec(timenow.minutes);
        LCD_OutString(" ");
        LCD_OutUDec(timenow.seconds);
        LCD_OutString(" ");
        LCD_OutUFloat(estMag.p[2],4);
        LCD_OutString(" ");
        angRate=angRatea;
        timepas=timenow;

        free(solEst.p);
        free(estMag.p);
        free(angRatea.p);
        free(vecSol.p);
        for(i=0;i<8000;i++){};

    }*/

    while(1)
    {
        conde++;
        UART_OutString("&\t");
        UART_OutUDec(conde);
        UART_OutString("|\t");
        kd=ADCS(kd);
        //vuelta++;
        //LCD_OutUDec(memoria);
        //LCD_OutString(" ");
        //LCD_OutUDec(conde);

    }


    int i,j;
    float *pa, a[3][3] = {{1, 2, 3},{4, 5, 6},{7,8,8}};
    float b[2][3] = {{1, 2, 3},{4, 5, 6}};
    float ra[3][3];
    float rb[3][3];
    float *rS,rSol[3]={1, 0, 0};
    float *rM,rMag[3]={2,5, 4};

    rS=rSol;
    rM=rMag;

    VECTOR refSol=Vinit(3);
    refSol=Vasign(refSol,rS);
    refSol.willFree=1;
    VECTOR refMag=Vinit(3);
    refMag=Vasign(refMag,rM);
    refMag.willFree=1;

    refMag=Vnorm(refMag);

    MATRIZ rotP=Mmul(ROT_X(30),ROT_Z(45));
    rotP.willFree=1;

    VECTOR medSol=m2vec(Mtrans(Mmul(rotP,Mtrans(vec2m(refSol)))));
    medSol.willFree=1;
    VECTOR medMag=m2vec(Mtrans(Mmul(rotP,Mtrans(vec2m(refMag)))));
    medMag.willFree=1;

    QUAT q=QUEST(refMag,refSol, medMag,medSol);
    MATRIZ TRID=TRIAD(refSol,refMag,medSol,medMag);
    for(i=0;i<TRID.dim[0];i++)
    {
        for(j=0;j<TRID.dim[1];j++)
        {
            ra[i][j]=TRID.p[i][j];
        }
    }


	return 0;
}

kalman_data ADCS(kalman_data kd)
{

    int i,j;


    ///Para casos de prueba se usarán datos predefinidos en esta seccion
    time_stat timenow;
    parOrb param;
    param.semiMayor=13341;//km
    param.excent=0.1;//0-1
    param.incl=10;//°
    param.ascDer=0;//°
    param.periArg=0;//°
    param.anomVerd=0;//°
    float t=100;
    float t0=0;
    float dt=0.5;

    /*int a=2022;
    int m=07;
    int d=24;
    int h=06;
    int min=02;
    int s=0;*/
    //Magnetorque de control
    MATRIZ N=Minit(3,1);
    N.p[0][0]=0;
    N.p[1][0]=0;
    N.p[2][0]=0;

    //Adquisicion de datos

    //Magnetometro
    VECTOR mag;
    //lecturaMag(&ang[0])
    //Giroscopio
    VECTOR gyro;
    //lecturaGyro(&gyro[0])
    //Celdas solare
    uint32_t sol_raw_v[6];
    uint32_t sol_raw_i[6];
    uint32_t sol_raw_t[6];
    uint32_t pot[6];

    readDS3231(&timenow);


    int configHMC[3]={0x70,0x00,0x00};
    int configL3G1[6]={0x0F,0x06,0x00,0x30,0x10,0x00};//(inicio, filtro, NA ,dps, filtro ENABLE,)

    VECTOR sol=lecturaSol(&sol_raw_v[0],&sol_raw_i[0],&sol_raw_t[0],&pot[0]);

    VECTOR vecSol,vecMag,angRatea,solEst;

    angRatea=lecturaGyro(&configL3G1[0]);
    vecMag=lecturaMag(&configHMC[0]);
    lecturaADC(6,&sol_raw_v[0],&sol_raw_i[0],&sol_raw_t[0]);
    vecSol=lecturaSol(&sol_raw_v[0],&sol_raw_i[0],&sol_raw_t[0],&pot[0]);
    solEst=estSol(timenow);


    //Propagación de la órbita
    param=propOrb(param,t,t0);
    //Estimación del campo magnético
    //Recibe la posición dada por el propagador orbital
    //magField B_N=earthmagfield13(r_N,ta,g0,13);
    MATRIZ POS=Minit(3,1);
    float posMx[3][1];
    float lat=19.35361111;
    float lng=-99.12833333;
    float alt=6373+2.29;
    float wr=2*PI/(3600*24);
    t=3600*(timenow.hour)+60*timenow.minutes+timenow.seconds;
    posMx[0][0]=alt*sind(lat);
    posMx[1][0]=alt*cosd(lat)*cosd(lng);
    posMx[2][0]=alt*cosd(lat)*sind(lng);
    POS=Masign(POS,&posMx[0][0]);
    MATRIZ rotd=ROT_Z((180/PI)*wr*t);
    //MATRIZ rotd=ROT_Z(0);
    POS=Mmul(rotd,POS);
    posMx[0][0]=POS.p[0][0];
    posMx[1][0]=POS.p[1][0];
    posMx[2][0]=POS.p[2][0];
    VECTOR B_N=earthmagfield13(posMx,t,lng*PI/180,13);

    //vecMag=m2vec(Mtrans(Mmul(Minv(rotd),Mtrans(vec2m(vecMag)))));
    //vecMag=m2vec(Mtrans(Mmul(rotd,Mtrans(vec2m(vecMag)))));//este es el bueno
    //Estimación del vector solar
    time_stat time2;
    //VECTOR estSolar=estSol(time2);
    QUAT q;
    MATRIZ A;


    //Desviacion del sensor
    MATRIZ Rs=MinitZ(3,3);
    MATRIZ Rm=MinitZ(3,3);
    Rs.p[0][0]=0.3*0.3;
    Rs.p[1][1]=0.3*0.3;
    Rs.p[2][2]=0.3*0.3;
    Rm.p[0][0]=0.1*0.1;
    Rm.p[1][1]=0.1*0.1;
    Rm.p[2][2]=0.1*0.1;


    B_N=Vnorm(B_N);
    solEst=Vnorm(solEst);
    vecMag=Vnorm(vecMag);
    vecSol=Vnorm(vecSol);

    //A=TRIAD(B_N,solEst,vecMag,vecSol);
    A=TRIAD(solEst,B_N,vecSol,vecMag);
    A=TRIAD(B_N,solEst,vecMag,vecSol);
    q=QUEST(B_N,solEst,vecMag,vecSol);
    A.willFree=1;
    MATRIZ A2=c2rot(Ccon(q));
    kalman_data kdn=kalmanInit();
    VECTOR giro=Vinit(3);
    giro.p[0]=0.1;
    giro.p[1]=0.1;
    giro.p[2]=0.1;

    //kdn=EKF(kd,kdn,A, angRatea, dt);
    //kdn=predEKF(kd,kdn, dt,angRatea,N);
    //kdn.x_n=kdn.x_es;
    //kdn.P_n=kdn.P_es;
    //kdn=correcEKF(kd, kdn, Rs,vecSol,solEst,A);

    //kdn=correcEKF(kd, kdn, Rm,vecMag,B_N,A);

    float alpha, beta,gama;
    float alpha2, beta2,gama2;
    alpha=atan2(A.p[1][0],A.p[0][0])*180/PI;
    beta=atan2(-A.p[2][0],sqrt(pow(A.p[2][1],2))+pow(A.p[2][2],2))*180/PI;
    gama=atan2(A.p[2][1],A.p[2][2])*180/PI;

    alpha2=atan2(A2.p[1][0],A2.p[0][0])*180/PI;
    beta2=atan2(-A2.p[2][0],sqrt(pow(A2.p[2][1],2))+pow(A2.p[2][2],2))*180/PI;
    gama2=atan2(A2.p[2][1],A2.p[2][2])*180/PI;

    QUAT rotkal;
    //rotkal.q[0]=kdn.x_n.p[0][0];
    //rotkal.q[1]=kdn.x_n.p[1][0];
    //rotkal.q[2]=kdn.x_n.p[2][0];
    //rotkal.q[3]=kdn.x_n.p[3][0];

    //MATRIZ Ak=c2rot(rotkal);


    MATRIZ OR=Minit(3,1);
    OR.p[0][0]=1;
    OR.p[1][0]=0;
    OR.p[2][0]=0;
    OR.willFree=1;
    //OR=Mmul(Ak,OR);
    MATRIZ ORsol=Mmul(A,Mtrans(vec2m(solEst)));
    MATRIZ ORmag=Mmul(A,Mtrans(vec2m(B_N)));

    LCD_Clear();
    OutCmd(0x80);
    LCD_OutUFloat(OR.p[0][0],4);
    LCD_OutString(" ");
    LCD_OutUFloat(OR.p[1][0],4);
    OutCmd(0xC0);
    LCD_OutUFloat(OR.p[2][0],4);
    LCD_OutString(" ");
    LCD_OutUFloat(vecSol.status,4);



    UART_OutUDec(timenow.hour);
    UART_OutString("\t");
    UART_OutUDec(timenow.minutes);
    UART_OutString("\t");
    UART_OutUDec(timenow.seconds);
    UART_OutString("\t");
    UART_OutUFloat(vecSol.p[0],4);
    UART_OutString("\t");
    UART_OutUFloat(vecSol.p[1],4);
    UART_OutString("\t");
    UART_OutUFloat(vecSol.p[2],4);
    UART_OutString("\t");
    UART_OutUFloat(vecSol.status,4);
    UART_OutString("\t");
    UART_OutUFloat(vecMag.p[0],4);
    UART_OutString("\t");
    UART_OutUFloat(vecMag.p[1],4);
    UART_OutString("\t");
    UART_OutUFloat(vecMag.p[2],4);
    UART_OutString("\t");
    UART_OutUFloat(OR.p[0][0],4);
    UART_OutString("\t");
    UART_OutUFloat(OR.p[1][0],4);
    UART_OutString("\t");
    UART_OutUFloat(OR.p[2][0],4);
    UART_OutString("\t");
    UART_OutUFloat((vecSol.p[0]-ORsol.p[0][0])*100/vecSol.p[0],4);
    UART_OutString("\t");
    UART_OutUFloat((vecSol.p[1]-ORsol.p[1][0])*100/vecSol.p[1],4);
    UART_OutString("\t");
    UART_OutUFloat((vecSol.p[2]-ORsol.p[2][0])*100/vecSol.p[2],4);
    UART_OutString("\t");
    UART_OutUFloat((vecMag.p[0]-ORmag.p[0][0])*100/vecMag.p[0],4);
    UART_OutString("\t");
    UART_OutUFloat((vecMag.p[1]-ORmag.p[1][0])*100/vecMag.p[1],4);
    UART_OutString("\t");
    UART_OutUFloat((vecMag.p[2]-ORmag.p[2][0])*100/vecMag.p[2],4);
    UART_OutString("\t");
    UART_OutString("\n");
/*
    UART_OutUFloat(kd.P_n.p[4][4],4);
    UART_OutString("\t");
    UART_OutUFloat(kd.P_n.p[4][5],4);
    UART_OutString("\t");
    UART_OutUFloat(kd.P_n.p[4][6],4);
    UART_OutString("\n");
    UART_OutUFloat(kd.P_n.p[5][4],4);
    UART_OutString("\t");
    UART_OutUFloat(kd.P_n.p[5][5],4);
    UART_OutString("\t");
    UART_OutUFloat(kd.P_n.p[5][6],4);
    UART_OutString("\n");
    UART_OutUFloat(kd.P_n.p[6][4],4);
    UART_OutString("\t");
    UART_OutUFloat(kd.P_n.p[6][5],4);
    UART_OutString("\t");
    UART_OutUFloat(kd.P_n.p[6][6],4);
    UART_OutString("\n \n");*/

/*
    if (sol.status>0.5)
    {
        if (sol.status>0.8)
        {
            if(mag.status>0.6)
            {
                q=QUEST(B_N,solEst,mag,sol);
                A=c2rot(q);

            }
            else
            {
                q=QUEST(solEst,solEst,sol,sol);
                A=c2rot(q);

            }
        }
        else
        {
            if(mag.status>0.6)
            {
                A=TRIAD(B_N,solEst,mag,sol);
                q=rot2c(A);
            }
            else
            {
                A=TRIAD(solEst,B_N,sol,mag);
                q=rot2c(A);
            }
        }
    }
    else
    {
        if(mag.status>0.6)
        {
            q=QUEST(B_N,B_N,mag,mag);
            A=c2rot(q);
        }
        else
        {
            q=q;
            A=c2rot(q);
        }

    }*/
    //free(OR.p);
    //free(B_N.p);

    //free(A.p);
    //free(vecSol.p);
    //free(vecMag.p);
    //free(angRatea.p);
    //free(solEst.p);
    //free(mag.p);
    //free(gyro.p);
    //free(sol.p);


/*

    //param=propOrb(param,t,t0);
    float *rS,rSol[3]={1, 0, 0};
    float *rM,rMag[3]={2, 5, 4};
    float lat=19.3536111;
    float lng=-99.128333;
    float alt=6373+2.229;
    float h=12;
    float m=00;
    float r_N[3][1];
    r_N[2][0]=alt*sind(lat);
    r_N[0][0]=alt*cosd(lat)*cosd(lng);
    r_N[1][0]=alt*cosd(lat)*sind(lng);
    float ta=3600*h+60*m;
    float g0=0;

    rS=rSol;
    rM=rMag;

    VECTOR refSol={rS,3};
    refSol.willFree=1;
    VECTOR refMag={rM,3};
    refMag.willFree=1;

    //refSol=estSol();

    refMag=Vnorm(refMag);
    refSol=Vnorm(refSol);

    MATRIZ rotP=Mmul(ROT_X(30),ROT_Z(45));
    rotP.willFree=1;

    VECTOR medSol=m2vec(Msum(Mtrans(Mmul(rotP,Mtrans(vec2m(refSol)))),Mrand(1,3)));
    medSol.willFree=1;
    VECTOR medMag=m2vec(Msum(Mtrans(Mmul(rotP,Mtrans(vec2m(refMag)))),Mrand(1,3)));
    medMag.willFree=1;

    QUAT q=QUEST(refMag,refSol, medMag,medSol);
    MATRIZ TRID=TRIAD(refSol,refMag,medSol,medMag);
    QUAT qd=rot2c(rotP);
    QUAT EQ=Cerr(qd,qd);
    QUAT Eq=Cerr(qd,Ccon(q));
    int d=0;
    free(TRID.p);
    free(medMag.p);
    free(medSol.p);
    free(refMag.p);
    free(refSol.p);
*/
    return kdn;
}

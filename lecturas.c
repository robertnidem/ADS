/*
 * lecturas.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */


#include<stdint.h>
#include<math.h>
#include"structs.h"
#include"vector.h"
#include"matrix.h"
#include"tm4c.h"
#include"adc.h"
#include"HMC5883L.h"
#include"L3GD20H.h"
#include"lecturas.h"
#include"lcd.h"


VECTOR lecturaSol(uint32_t* v_rawdata,uint32_t* i_rawdata, uint32_t* temp_raw,uint32_t* pot)
{
    /*
     * Descripción:
     * Este codigo utiliza las lecturas de voltaje corriente y temperatura de las celdas solares
     * para determinar el ángulo de incidencia del sol sobre cada una de las celdas
     * para generar el vector de sol.
     *
     * ------------------------------------------------------------------------------
     *
     * INPUTS
     *
     * v_rawdata        [6]     valores de voltaje medidos por el puerto ADC        [V]
     * i_rawdata        [6]     valores de corriente medidos por el puerto ADC      [V]
     * t_rawdata        [6]     valores de temperatura medidos por el puerto ADC    [V]
     *
     * -------------------------------------------------------------------------------
     *
     * OUTPUTS
     *
     * sun        [VECTOR]   Estructura que contiene el vector de sol normalizado y
     *                          el coeficiente de proporción del mismo
     *
     * -------------------------------------------------------------------------------
     */
    int i;
    int refSol=1367; //[W/m^2] Valor de irradiancia solar
    int Rdv1=10000;//[Ohms]   Datos de la instrumentación necesarios para determinar los valores reales
    int Rdv2=10000;//[Ohms]
    float Rs=1;//Resistencia de Shunt [Ohms]
    int Gamp=100;//Ganancia del amplificador Operacional
    float A=0.053*0.03;//Area de la celda [m^2]
    float Vm[6],Im[6],Pm[6],Pr[6],Tm[6];
    float beta=4050.0;//coeficiente del termistor

    for (i=0;i<6;i++)//En este ciclo se convierten los valores de voltaje en corriente y temperatura respectivamente
    {
        Vm[i]=(*(v_rawdata+i)*3.3/4095.0)*((Rdv1+Rdv2)/Rdv2);   //Se obtiene el valor de voltaje real a la entrada del divisor de voltaje
        Im[i]=(*(i_rawdata+i)*3.3/4095.0)/(Rs*Gamp);            //Se calcula la corriente en la Resistencia de shunt por ley de Ohm

        //Pm[i]=((*(v_rawdata +i)*3.3/4095.0)*(Rdv1+Rdv2)/Rdv2)*((*(i_rawdata+i)*3.3/4095.0)/(Rs*Gamp));
        Pm[i]=Vm[i]*Im[i];                                      //Se calcula la potencia generada por la celda
        *(pot+i)=Pm[i];                                         //Se guarda este valor en un arreglo en el main
        //Pr[i]=refSol*A*(-0.0007*((*(temp_raw+i)*5/4095))+0.1261);
        Tm[i]=(1.0/298.15)+(1.0/beta)*log((4096.0/ *(temp_raw+i))-1.0);//Se utiliza la ecuación del termistor para obtener la temperatura
        Tm[i]=1/Tm[i]-273.15;                                          //dado el voltaje recibido
        //Tm[i]=*(temp_raw+i)*3.3/4095.0;
        Pr[i]=refSol*A*(-0.00006*(Tm[i])+0.0173);               //Se obtiene la potencia teórica de la celda generando la eficiencia
                                                                //en función de la temperatura
    }


    /*LCD_Clear();
    OutCmd(0x80);

    LCD_OutUFloat(Vm[0],4);
    LCD_OutString(" ");
    LCD_OutUFloat(Im[0],4);
    OutCmd(0xC0);

    LCD_OutUFloat(Tm[0],4);
    LCD_OutString(" ");
    LCD_OutUFloat(Vm[3],4);*/

    float ang[3];//Aqui se guardará el ángulo de incidencia del eje correspondiente
    float apre[3];//
    float aprete[3];//Se guardarán los valores de potencia teórica correspondientes

    //Se compara por pares de caras cuál valor es mayor y se guarda en un arreglo de 3 datos

    if (Pm[0]>=Pm[3])//Eje X, celdas 0 y 3
    {
        ang[0]=acosd(Pm[0]/Pr[0]);
        apre[0]=Pm[0];//Se guarda el valor de potencia mayor en una arreglo
        aprete[0]=Pr[0];
    }
    else
    {
        ang[0]=180-acosd(Pm[3]/Pr[3]);//si es en dirección -X se obtiene so complemento
        apre[0]=Pm[3];
        aprete[0]=Pr[3];
    }

    if (Pm[1]>=Pm[4])//Eje Y, celdas 1 y 4
    {
        ang[1]=acosd(Pm[1]/Pr[1]);
        apre[1]=Pm[1];
        aprete[1]=Pr[1];
    }
    else
    {
        ang[1]=180-acosd(Pm[4]/Pr[4]);
        apre[1]=Pm[4];
        aprete[1]=Pr[4];
    }

    if (Pm[2]>=Pm[5])//Eje Z, celdas 2 y 5
    {
        ang[2]=acosd(Pm[2]/Pr[2]);
        apre[2]=Pm[2];
        aprete[2]=Pr[2];
    }
    else
    {
        ang[2]=180-acosd(Pm[5]/Pr[5]);
        apre[2]=Pm[5];
        aprete[2]=Pr[5];
    }

    float normR=0,norm=0;

/*
    for (i=0;i<6;i++)
    {
        normR=normR+Pr[i];
    }*/
    normR=sqrt(aprete[0]*aprete[0]+aprete[1]*aprete[1]+aprete[2]*aprete[2]);//Se obtiene el módulo de la potencia teórica de las celdas seleccionadas
    norm=sqrt(apre[0]*apre[0]+apre[1]*apre[1]+apre[2]*apre[2]);//Se calcula el módulo de la potencia obtenida por las celdas
    VECTOR sun=Vinit(3);//Se crea un vector de dimensión 3 para guardar el vector de sol
    sun.status=norm/(normR);//Se obtiene la relación entre módulo de las mediciones y módulo esperado, para determinar que tan confiable es
    sun.p[0]=cosd(ang[0]);//Se convierten los ángulos calculados previamente en componentes vectoriales
    sun.p[1]=cosd(ang[1]);
    sun.p[2]=cosd(ang[2]);
    sun.willFree=1;
    //sun.status=Vmod(sun)/1;

    sun=Vnorm(sun);//Se normaliza el vector
    return sun;



}
void PortK_Init()//Activa  el puerto K como salidas digitales
{
    SYSCTL_RCGCGPIO_R |= 0x200; //Activa el reloj del puerto K

    while ((SYSCTL_PRGPIO_R & 0x200) == 0){};  // reloj listo?


    GPIO_PORTK_DIR_R |= 0xFF;    // puerto L de salida
    GPIO_PORTK_DEN_R |= 0xFF;    // habilita el puerto L
    GPIO_PORTK_AFSEL_R |=0x00;
    GPIO_PORTK_ODR_R |= 0x00;



}

void PortL_Init()//Activa  el puerto L como salidas digitales
{
    SYSCTL_RCGCGPIO_R |= 0x400; //Activa el reloj del puerto L

    while ((SYSCTL_PRGPIO_R & 0x400) == 0){};  // reloj listo?


    GPIO_PORTL_DIR_R |= 0x0F;    // puerto L de salida
    GPIO_PORTL_DEN_R |= 0x0F;    // habilita el puerto L
    GPIO_PORTL_AFSEL_R |=0x00;
    GPIO_PORTL_ODR_R |= 0x00;



}


void lecturaADC(int num, uint32_t* v, uint32_t* i, uint32_t* t)
{
    //Recorre el puerto L0, L1 ,L2 para dar direcciones al multiplexor
    //Lee los valores analógicos en el puerto E0, E1, E2
    int j,d;
    GPIO_PORTL_DATA_R= 0x00;
    for (j=0;j<num;j++)
    {
        GPIO_PORTL_DATA_R= j;

        /*ADC0_PSSI_R=0x0004;//iniciar la conversion
        while((ADC0_RIS_R& 0x04)==0);

        *(v+j)=(ADC0_SSFIFO2_R&0xFFF);
        *(i+j)=(ADC0_SSFIFO2_R&0xFFF);
        *t=(ADC0_SSFIFO2_R&0xFFF);
        ADC0_ISC_R= 0X0004;//limpiar bandera*/



        ADC_Read((v+j),(i+j),(t+j));
        for (d=0;d<80000;d++){}//delay



    }
}

VECTOR lecturaMag(int* config)
{///Falta implementar escala de temperatura
    /*
     * 000= +-0.88   0.00073     0x00
     * 001= 1.3      0.00092     0x20
     * 010= 1.9      0.00122     0x40
     * 011= 2.5      0.00152     0x60
     * 100= 4.0      0.00227     0x80
     * 101= 4.7      0.00256     0xA0
     * 110= 5.6      0.00303     0xC0
     * 111= 8.1      0.00435     0xE0
     */
    uint8_t raw_data[6];
    short data[3];
    readHMC5883L(&raw_data[0]);
    data[0]=(raw_data[1]+(raw_data[0]<<8));//X
    data[1]=(raw_data[5]+(raw_data[4]<<8));//Y
    data[2]=(raw_data[3]+(raw_data[2]<<8));//Z

    //GPIO_PORTK_DATA_R=raw_data[1];

    VECTOR magField=Vinit(3);

    switch(config[1])
    {
    case 0x00:

        magField.p[0]=(float)data[0]*0.0007303f;
        magField.p[1]=(float)data[1]*0.0007303f;
        magField.p[2]=(float)data[2]*0.0007303f;

        break;
    case 0x20:

        magField.p[0]=(float)data[0]*0.00092f;
        magField.p[1]=(float)data[1]*0.00092f;
        magField.p[2]=(float)data[2]*0.00092f;

        break;
    case 0x40:

        magField.p[0]=(float)data[0]*0.00122f;
        magField.p[1]=(float)data[1]*0.00122f;
        magField.p[2]=(float)data[2]*0.00122f;

        break;
    case 0x60:

        magField.p[0]=(float)data[0]*0.00152f;
        magField.p[1]=(float)data[1]*0.00152f;
        magField.p[2]=(float)data[2]*0.00152f;

        break;
    case 0x80:

        magField.p[0]=(float)data[0]*0.00227f;
        magField.p[1]=(float)data[1]*0.00227f;
        magField.p[2]=(float)data[2]*0.00227f;

        break;
    case 0xA0:

        magField.p[0]=(float)data[0]*0.00256f;
        magField.p[1]=(float)data[1]*0.00256f;
        magField.p[2]=(float)data[2]*0.00256f;

        break;
    case 0xC0:

        magField.p[0]=(float)data[0]*0.00303f;
        magField.p[1]=(float)data[1]*0.00303f;
        magField.p[2]=(float)data[2]*0.00303f;

        break;
    case 0xE0:

        magField.p[0]=(float)data[0]*0.00435f;
        magField.p[1]=(float)data[1]*0.00435f;
        magField.p[2]=(float)data[2]*0.00435f;

        break;
    default:

        magField.p[0]=(float)data[0]*0.00092f;
        magField.p[1]=(float)data[1]*0.00092f;
        magField.p[2]=(float)data[2]*0.00092f;

    }


    magField.willFree=1;
    return magField;
}


VECTOR lecturaGyro(int* config)
{
    uint8_t raw_data[6];
    short data[3];
    readL3GD20H(&raw_data[0]);
    data[0]=(raw_data[0]+(raw_data[1]<<8));
    data[1]=(raw_data[2]+(raw_data[3]<<8));
    data[2]=(raw_data[4]+(raw_data[5]<<8));

    VECTOR angRate=Vinit(3);

    if (config[3]==0x00)
    {
        angRate.p[0]=(float)data[0]*0.00875;
        angRate.p[1]=(float)data[1]*0.00875;
        angRate.p[2]=(float)data[2]*0.00875;
    }
    if(config[3]==0x10)
    {
        angRate.p[0]=(float)data[0]*0.0175;
        angRate.p[1]=(float)data[1]*0.0175;
        angRate.p[2]=(float)data[2]*0.0175;
    }
    if(config[3]==0x30)
    {

        angRate.p[0]=(float)data[0]*0.07;
        angRate.p[1]=(float)data[1]*0.07;
        angRate.p[2]=(float)data[2]*0.07;
    }


    //GPIO_PORTK_DATA_R=(int)angRate.p[2];
    angRate.willFree=1;
    return angRate;
}






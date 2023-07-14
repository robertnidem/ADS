/*
 * adc.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#include<stdint.h>
#include<stdbool.h>
#include"tm4c.h"
#include"adc.h"

void ADC0_Init()
{
    SYSCTL_RCGCGPIO_R |= 0x10; //Habilita el reloj para el puerto E
    while((SYSCTL_PRGPIO_R & 0x10) == 0); // Se espera a que el reloj se estabilice

    GPIO_PORTE_AHB_DIR_R = 0x00; //PE 0,1,2 ENTRADAS
    GPIO_PORTE_AHB_AFSEL_R |= 0x07;  //Habilita función alterna en PE 0,1,2
    GPIO_PORTE_AHB_DEN_R &= ~0x07;  //Deshabilita la función digital en PE 0,1,2
    GPIO_PORTE_AHB_AMSEL_R |= 0x07; //Habilita la función analógica


    SYSCTL_RCGCADC_R |= 0x01; //Habilita el reloj en ADC0
    while((SYSCTL_PRADC_R & 0x01) == 0); // Se espera a que el reloj se estabilice


    ADC0_PC_R = 0x01;
    ADC0_SSPRI_R= 0x0123;
    ADC0_ACTSS_R &= ~0x0004; //Deshabilita  SS2
    ADC0_EMUX_R = 0x0000; //Tipo de evento trigger
    ADC0_SAC_R = 0x0;
    ADC0_CTL_R = 0x0;
    ADC0_SSOP2_R = 0x0000;
    ADC0_SSTSH2_R = 0X000;

    ADC0_SSMUX2_R = 0x0123; //Primera muestra AIN3, Segunda muestra AIN2, TERCERA MUESTRA AIN1
    ADC0_SSEMUX2_R &= ~0x111;//Selecciona AIN[19-16]
    ADC0_SSCTL2_R= 0x0600;//La tercer muestra es el fin de la cadena
    ADC0_IM_R &= ~0x0004;
    ADC0_ACTSS_R |= 0x0004;


    SYSCTL_PLLFREQ0_R |= 0x00800000;  // encender PLL
    while((SYSCTL_PLLSTAT_R&0x01)==0);            // espera a que el PLL fije su frecuencia
    SYSCTL_PLLFREQ0_R &= ~0x00800000; // apagar PLL


    ADC0_ISC_R = 0x0004;  // Se recomienda Limpia la bandera RIS del ADC0

}

void ADC_Read(uint32_t* v, uint32_t* i, uint32_t* t)
{
    int conde;
    ADC0_PSSI_R=0x0004;//iniciar la conversion
    while((ADC0_RIS_R& 0x04)==0);

    *v=(ADC0_SSFIFO2_R&0xFFF);
    for(conde=0;conde<400;conde++){}
    *i=(ADC0_SSFIFO2_R&0xFFF);
    for(conde=0;conde<400;conde++){}
    *t=(ADC0_SSFIFO2_R&0xFFF);
    for(conde=0;conde<400;conde++){}
    ADC0_ISC_R= 0X0004;//limpiar bandera

}



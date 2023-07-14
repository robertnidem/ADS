/*
 * HMC5883L.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */
#include<stdint.h>
#include"wire.h"
#include"HMC5883L.h"

void readHMC5883L(uint8_t* mag_raw)
{
    while(I2C0ready()){};
    I2C0begin(DirHMC5883L,MOUT_X_M);
    int i,j;
    for(i=0;i<6;i++)
    {
        *(mag_raw+i)=I2C0read(DirHMC5883L);
        for (j=0;j<400;j++);
    }

    I2C0stop();

}

void configHMC5883L(int* data, int bytes)
{

    /*REGA= X MA1 MA0 DO2 DO1 DO0 MS1 MS0
     *      MA1 MA0 muestras promedio 00=1   01=2   10=4    11=8
     *      DO2 DO1 DO0 Data Output Rate 100 = 15Hz Default
     *      MS1 MS0 modo de medicion 00=modo normal def
     *
     * REGB GN2 GN1 GN0 0 0 0 0
     *      GN2 GN1 GN0 Ganancia  000= +-0.88   0.00073     0x00
     *                            001= 1.3      0.00092     0x20
     *                            010= 1.9      0.00122     0x40
     *                            011= 2.5      0.00152     0x60
     *                            100= 4.0      0.00227     0x80
     *                            101= 4.7      0.00256     0xA0
     *                            110= 5.6      0.00303     0xC0
     *                            111= 8.1      0.00435     0xE0
     *
     * Mode Register HS 0 0 0 0 0 MD1 MD0
     *      HS=High Speed
     *      MD1 MD0 modo de operacion   00 medicion continua
     *                                  01 medicion unica
     *                                  1x modo de espera
     *
     *
     */
    int i;
    while (I2C0ready()){};
    I2C0begin(DirHMC5883L,CONFIGRA);
    //I2C0write(0x70);
    //I2C0write(0x00);
    //I2C0writeS(0x00);
    for(i=0;i<bytes-1;i++)
    {
        I2C0write(data[i]);
    }
    I2C0writeS(data[bytes-1]);


}






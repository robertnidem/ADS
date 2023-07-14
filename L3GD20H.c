/*
 * L3GD20H.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */


#include<stdint.h>
#include"wire.h"
#include"L3GD20H.h"
void readL3GD20H(uint8_t* gyro_raw)
{
    while(I2C0ready()){};
    I2C0begin(DirL3GD20H,OUT_X_L);
    *gyro_raw=I2C0read(DirL3GD20H);
    I2C0stop();

    I2C0begin(DirL3GD20H,OUT_X_H);
    *(gyro_raw+1)=I2C0read(DirL3GD20H);
    I2C0stop();

    I2C0begin(DirL3GD20H,OUT_Y_L);
    *(gyro_raw+2)=I2C0read(DirL3GD20H);
    I2C0stop();


    I2C0begin(DirL3GD20H,OUT_Y_H);
    *(gyro_raw+3)=I2C0read(DirL3GD20H);
    I2C0stop();


    I2C0begin(DirL3GD20H,OUT_Z_L);
    *(gyro_raw+4)=I2C0read(DirL3GD20H);
    I2C0stop();


    I2C0begin(DirL3GD20H,OUT_Z_H);
    *(gyro_raw+5)=I2C0read(DirL3GD20H);
    I2C0stop();
}

void configL3GD20H(int* data)
{
    while(I2C0ready()){};
    /*I2C0begin(DirL3GD20H,dir);//0x0F,0x09,0x00,0x30

    for(i=0;i<bytes-1;i++)
    {
        I2C0write(data[i]);
    }
    I2C0writeS(data[bytes-1]);*/

    I2C0begin(DirL3GD20H,CTRL1);// DR1 DR0 BW1 BW0 PD Zen Xen Yen
    I2C0writeS(data[0]);

    I2C0begin(DirL3GD20H,CTRL2);// X X HPM1 HPM0 HPCF3 HPCF2 HPCF1 HPCF0
    I2C0writeS(data[1]);

    I2C0begin(DirL3GD20H,CTRL3);// X X X X X X X X
    I2C0writeS(data[2]);

    I2C0begin(DirL3GD20H,CTRL4);// X X FS1 FS0 X X X X
    I2C0writeS(data[3]);

    I2C0begin(DirL3GD20H,CTRL5); // X X X HPen  X X X X
    I2C0writeS(data[4]);

    I2C0begin(DirL3GD20H,LOW_ODR);// X X X X X X X LOW_ODR
    I2C0writeS(data[5]);

}




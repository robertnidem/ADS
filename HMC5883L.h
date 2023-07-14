/*
 * HMC5883L.h
 *
 *  Created on: 27 jul 2022
 *      Author: rober
 */

#ifndef HMC5883L_H_
#define HMC5883L_H_

#define DirHMC5883L  0x1E
#define DirHMC5883LR 0x1D

#define CONFIGRA    0x00
#define CONFIGRB    0x01
#define MODREG      0x02
#define MOUT_X_M     0x03
#define MOUT_X_L     0x04
#define MOUT_Z_M     0x05
#define MOUT_Z_L     0x06
#define MOUT_Y_M     0x07
#define MOUT_Y_L     0x08
#define MSTATUS      0x09
#define ID_REG_A    0x0A
#define ID_REG_B    0x0B
#define ID_REG_C    0x0C

void readHMC5883L(uint8_t* mag_raw);

void configHMC5883L(int* data, int bytes);

#endif /* HMC5883L_H_ */

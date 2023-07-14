/*
 * lecturas.h
 *
 *  Created on: 21 jul 2022
 *      Author: rober
 */

#ifndef LECTURAS_H_
#define LECTURAS_H_



VECTOR lecturaSol(uint32_t* v_rawdata,uint32_t* i_rawdata, uint32_t* temp_raw,uint32_t* pot);
void PortK_Init();//Activa  el puerto K como salidas digitales;

void PortL_Init();//Activa  el puerto L como salidas digitales;

void lecturaADC(int num, uint32_t* v, uint32_t* i, uint32_t* t);

VECTOR lecturaMag(int* config);
VECTOR lecturaGyro(int* config);
#endif /* LECTURAS_H_ */

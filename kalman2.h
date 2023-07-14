/*
 * kalman2.h
 *
 *  Created on: 16 ene 2023
 *      Author: rober
 */

#ifndef KALMAN2_H_
#define KALMAN2_H_


kalman_data2 kalman_Init2();
//kalman_data predEKF(kalman_data kd,MATRIZ Fi, MATRIZ P, MATRIZ xa, MATRIZ Q, MATRIZ Omega, MATRIZ wb, float dt, MATRIZ I, MATRIZ N);
kalman_data pred_EKF(kalman_data kd, kalman_data kdn, float dt, VECTOR gyro, MATRIZ N);

//kalman_data correcEKF(kalman_data kp,MATRIZ H, MATRIZ Pes, MATRIZ Xes, MATRIZ R, VECTOR med, VECTOR ref, MATRIZ rot);
kalman_data correc_EKF(kalman_data kp,kalman_data kdn, MATRIZ R, VECTOR med, VECTOR ref, MATRIZ rot);
//kalman_data EKF(kalman_data kd, MATRIZ A, QUAT q,VECTOR med, VECTOR ref, float dt);
kalman_data2 EKF2(kalman_data2 kd, kalman_data2 kdn, MATRIZ A,  VECTOR gyro, VECTOR medMag, VECTOR medSol, VECTOR refMag, VECTOR refSol, float dt);





#endif /* KALMAN2_H_ */

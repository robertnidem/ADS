/*
 * kalman.h
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#ifndef KALMAN_H_
#define KALMAN_H_


kalman_data kalmanInit();
//kalman_data predEKF(kalman_data kd,MATRIZ Fi, MATRIZ P, MATRIZ xa, MATRIZ Q, MATRIZ Omega, MATRIZ wb, float dt, MATRIZ I, MATRIZ N);
kalman_data predEKF(kalman_data kd, kalman_data kdn, float dt, VECTOR gyro, MATRIZ N);

//kalman_data correcEKF(kalman_data kp,MATRIZ H, MATRIZ Pes, MATRIZ Xes, MATRIZ R, VECTOR med, VECTOR ref, MATRIZ rot);
kalman_data correcEKF(kalman_data kp,kalman_data kdn, MATRIZ R, VECTOR med, VECTOR ref, MATRIZ rot);
//kalman_data EKF(kalman_data kd, MATRIZ A, QUAT q,VECTOR med, VECTOR ref, float dt);
kalman_data EKF(kalman_data kd, kalman_data kdn, MATRIZ A,  VECTOR gyro, float dt);




#endif /* KALMAN_H_ */

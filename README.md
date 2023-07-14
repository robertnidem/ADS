# ADS
Attitude Determination System for CubeSat 

Code of an attitude determination system for nano sattelite CubeSat 3U

Designed to test in Tiva TM4C1294XL Cortex M4 in C language

Contemplates use of sensors:

---Magnetometer HMC5883L

---Gyroscope L3GD20H

---Solar Cells Arrangement


Most important librarys:

--- matrix.h defines basic operations for matrixes of any dimention

--- vector.h defines basic operations for 2 and 3 dimension vectors

--- cuaternion.h defines basic operations for quaternions

--- structs.h defines the structs used on each library

--- rotacion.h defines the rotation matrix for each axis and the transformation matrix-quaternion

--- L3GD20H.h adress and registers of gyroscope

--- HMC5883L.h adress and registers of magnetomete

--- wire.h I2C conection functions

--- IGRF.h geomagnetic field estimator  based on IGRF13

--- estimadores.h TRIAD QUEST estimators and orbit propagator



Unfortantely this project wasn´t and won't be finished, some codes may not run or may need some work to be implemented on your projects but I hope it provides a guide to solve what you where looking for

For further questions contact me on  roberto.medina@ingenieria.unam.edu

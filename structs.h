/*
 * structs.h
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include<stdbool.h>
#include<stdint.h>
#include<math.h>


#define PI 3.141592653589793

#define rad(deg) ((deg)*(PI))/(180)
#define deg(rad) ((rad)*(180))/(PI)

#define cosd(ang) cos(((ang)*(PI))/180)
#define acosd(ang) ((acos(ang))*(180/PI))
#define sind(ang) sin(((ang)*(PI))/180)
#define asind(ang) ((asin(ang))*(180/PI))
#define tand(ang) tan(((ang)*(PI))/180)
#define atand(ang) ((atan(ang))*(180/PI))

struct VECTOR{
    float p[4];
    int dim;
    float status;
    bool willFree;//si 0 sera borrado el apuntador
};

typedef struct VECTOR VECTOR;


struct MATRIZ {
    float p[7][7];
    int dim[2];
    bool willFree;//SI 0 se borrará en la siguiente función
    float status;//acuasa un error
};

typedef struct MATRIZ MATRIZ;

struct QUAT{
        float q[4];
        bool status;
};
typedef struct QUAT QUAT;


struct time_stat
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;

};
typedef struct time_stat time_stat;

struct parOrb{
    float lat;
    float lng;
    float alt;
    float semiMayor;
    float excent;
    float incl;
    float ascDer;
    float periArg;
    float anomVerd;
    float pos[3][1];
};
typedef struct parOrb parOrb;


struct kalman_data{
    MATRIZ x_n;//estado actual
    MATRIZ P_n;//
    MATRIZ x_es;//estimacion de estado
    MATRIZ P_es;//
    MATRIZ Fi;//Matriz de trnsicion de estado
    MATRIZ H;//Matriz de observacion
    MATRIZ Q;//ruido de proceso y observacion
    MATRIZ I;//tensor de inercia
    MATRIZ Omega;//
    MATRIZ wb;//
    MATRIZ K;//Matriz de ganancia
};
typedef struct kalman_data kalman_data;


struct kalman_data2{
    MATRIZ x_n;
    MATRIZ x_es;
    MATRIZ x_esT;
    MATRIZ P_n;
    MATRIZ P_es;
    MATRIZ R;

};
typedef struct kalman_data2 kalman_data2;



#endif /* STRUCTS_H_ */

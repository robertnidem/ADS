/*
 * DS3231.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#include <stdlib.h>
#include <stdint.h>
#include "structs.h"
#include "wire.h"
#include "DS3231.h"

uint8_t convertValueIn(uint8_t value)
{
    return value- 6 *(value>>4);
}

uint8_t convertValueOut(uint8_t value)
{
    return value + 6 *(value/10);
}

void readDS3231(time_stat* times)
{
    while(I2C0ready()){};
    I2C0begin(DirDS3231,reg_second);

    times->seconds=convertValueIn(I2C0read(DirDS3231));
    times->minutes=convertValueIn(I2C0read(DirDS3231));
    times->hour=convertValueIn(I2C0read(DirDS3231));
    times->day=convertValueIn(I2C0read(DirDS3231));
    times->date=convertValueIn(I2C0read(DirDS3231));
    times->month=convertValueIn(I2C0read(DirDS3231));
    times->year =convertValueIn(I2C0read(DirDS3231));

    I2C0stop();
}
void configDS3231(time_stat* times)
{
    while(I2C0ready()){};
    I2C0begin(DirDS3231,reg_second);

    I2C0write(convertValueOut(times->seconds));
    I2C0write(convertValueOut(times->minutes));
    I2C0write(convertValueOut(times->hour));
    I2C0write(convertValueOut(times->day));
    I2C0write(convertValueOut(times->date));
    I2C0write(convertValueOut(times->month));
    I2C0writeS(convertValueOut(times->year));

}





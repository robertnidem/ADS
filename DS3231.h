/*
 * DS3231.h
 *
 *  Created on: 10 sep 2022
 *      Author: rober
 */

#ifndef DS3231_H_
#define DS3231_H_


#define DirDS3231 0x68

#define reg_second      0x00
#define reg_minute      0x01
#define reg_hour        0x02
#define reg_day         0x03
#define reg_date        0x04
#define reg_month       0x05
#define reg_year        0x06


uint8_t convertValueIn(uint8_t value);
uint8_t convertValueOut(uint8_t value);
void readDS3231(time_stat* times);
void configDS3231(time_stat* times);




#endif /* DS3231_H_ */

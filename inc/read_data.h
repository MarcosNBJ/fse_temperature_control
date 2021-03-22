#include<stdio.h>
#include<uart.h>
#include<unistd.h>
#include<stdlib.h>
#include "i2c.h"
#include "temperatures.h"

#ifndef READ_DATA_H_
#define READ_DATA_H_

void readTemperatures(TempInfo* temp);
void setUserDefined(float temperature);

#endif
#include<stdio.h>
#include<uart.h>
#include "lcd.h"
#include "log.h"
#include "bme280.h"
#include "i2c.h"
#include "gpio.h"
#include "pid.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "temperatures.h"
#include "menu.h"

#ifndef CONTROL_LOOP_H_
#define CONTROL_LOOP_H_

void control_loop();
void readTemperatures(TempInfo* temp);

#endif
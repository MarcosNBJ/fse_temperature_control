#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>

#ifndef GPIO_H_
#define GPIO_H_

void initGPIO ();
void setResistorOff();
void setFanOff();
void setFanOn(int activation);
void setResistorOn(int activation);
void setAllOff();
void adjustTemperature(double controlSignal);

#endif 

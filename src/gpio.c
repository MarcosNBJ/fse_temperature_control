#include "gpio.h"
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>

#define PIN_RESISTOR 4
#define PIN_FAN 5


void initGPIO(){
    wiringPiSetup ();
}
void setResistorOff(){
    pinMode(PIN_RESISTOR, OUTPUT);
    softPwmCreate(PIN_RESISTOR, 0,100);
    softPwmWrite(PIN_RESISTOR, 0);
}
void setFanOff(){
    pinMode(PIN_FAN, OUTPUT);
    softPwmCreate(PIN_FAN, 0,100);
    softPwmWrite (PIN_FAN, 0);
}
void setFanOn(int activation){
    setResistorOff();
    if(abs(activation) > 40){
        pinMode(PIN_FAN, OUTPUT);
        softPwmCreate(PIN_FAN, 0,100);
        softPwmWrite (PIN_FAN, abs(activation));
    }
    else{
        setFanOff();
    }
}
void setResistorOn(int activation){
    setFanOff();
    pinMode(PIN_RESISTOR, OUTPUT);
    softPwmCreate(PIN_RESISTOR, 0,100);
    softPwmWrite(PIN_RESISTOR, activation);
}
void setAllOff(){
    setResistorOff();
    setFanOff();
}

void adjustTemperature(double controlSignal){
    if(controlSignal>0){
        setResistorOn((int) controlSignal);
    }
    else{
        setFanOn((int) controlSignal);
    }

}
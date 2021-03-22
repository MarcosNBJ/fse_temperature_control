#include "gpio.h"

#define PIN_RESISTOR 4
#define PIN_FAN 5


void initGPIO(){
    //inits gpio with wiring pi
    wiringPiSetup ();
}
void setResistorOff(){
    //turns off resistor
    pinMode(PIN_RESISTOR, OUTPUT);
    softPwmCreate(PIN_RESISTOR, 0,100);
    softPwmWrite(PIN_RESISTOR, 0);
}
void setFanOff(){
    //turns off fan
    pinMode(PIN_FAN, OUTPUT);
    softPwmCreate(PIN_FAN, 0,100);
    softPwmWrite (PIN_FAN, 0);
}
void setFanOn(int activation){
    /*
     turns off resistor and turns on fan, if the intensity is above 40
     otherwise shuts down both
    */
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
    /*
      turns off fan and turns on resistor
    */
    setFanOff();
    pinMode(PIN_RESISTOR, OUTPUT);
    softPwmCreate(PIN_RESISTOR, 0,100);
    softPwmWrite(PIN_RESISTOR, activation);
}
void setAllOff(){
    //shuts down both, resistor and fan
    setResistorOff();
    setFanOff();
}

void adjustTemperature(double controlSignal){
    /*
        Receives control signal returned by PID
        a positive signal should turn on the resistor
        a negative should use the fan.
    */
    if(controlSignal>0){
        setResistorOn((int) controlSignal);
    }
    else{
        setFanOn((int) controlSignal);
    }

}
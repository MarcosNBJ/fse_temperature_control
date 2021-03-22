#include "i2c.h"
#define I2C_ADDR 0x76


void initI2C(){
    //initializing bme280Init
    
    bme280Init(1, I2C_ADDR);
}
float getExternalTemp(){
    //using bme280 to get ambient temperature information

    int T, P, H;
    bme280ReadValues(&T, &P, &H);
    return T/100.0;
}
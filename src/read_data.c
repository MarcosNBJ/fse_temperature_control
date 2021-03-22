#include "read_data.h"

volatile int isUserDefined=0; //flag to see if user wants to define temperature manually
volatile float userDefinedTemperature; //variable to receive user defined temperature

void setUserDefined(float temperature){
    /*
       if a -1 is received, the temperature should be from potentiometer
       otherwise, the user wants to enter the temperature manually 
    */
    if(temperature==-1){
        isUserDefined=0;
    }else{
        isUserDefined=1;
        userDefinedTemperature=temperature;
    }
}

void readTemperatures(TempInfo* temp){
    /*
       Reads external, internal and reference temperatures
    */

    //external temperature from bme and internal from UART
    temp->extTemperature = getExternalTemp();
    temp->intTemperature = getInternalTemp();

    //if the user defined the temperature manually, that's the reference temperature
    //otherwise, use potentiometer value from UART
    if(isUserDefined){
        temp->refTemperature = userDefinedTemperature;
    }else{
        temp->refTemperature = getPotentiometerTemp();
    }

    if(temp->refTemperature < temp->extTemperature){
          temp->refTemperature = temp->extTemperature;
    }

}

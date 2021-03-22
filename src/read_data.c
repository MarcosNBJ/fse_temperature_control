#include "read_data.h"

volatile int isUserDefined=0;
volatile float userDefinedTemperature;

void readTemperatures(TempInfo* temp){

    temp->extTemperature = getExternalTemp();
    temp->intTemperature = getInternalTemp();

    if(isUserDefined){
        temp->refTemperature=userDefinedTemperature;
    }else{
        temp->refTemperature = getPotentiometerTemp();
    }

}

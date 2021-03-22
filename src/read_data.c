#include "read_data.h"

volatile int isUserDefined=0;
volatile float userDefinedTemperature;

void setUserDefined(float temperature){
    if(temperature==-1){
        isUserDefined=0;
    }else{
        isUserDefined=1;
        userDefinedTemperature=temperature;
    }
}

void readTemperatures(TempInfo* temp){

    temp->extTemperature = getExternalTemp();
    temp->intTemperature = getInternalTemp();

    if(isUserDefined){
        temp->refTemperature=userDefinedTemperature;
    }else{
        temp->refTemperature = getPotentiometerTemp();
    }

}

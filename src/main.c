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

void quit() {
  lcd_init();
  setAllOff();
  exit(0);
}




void readTemperatures(TempInfo* temp){

    temp->extTemperature = getExternalTemp();
    temp->intTemperature = getInternalTemp();
    temp->refTemperature = getPotentiometerTemp();
}


int main(){
     signal(SIGINT,quit);
    lcd_init();
    I2C();
    initGPIO();
    createCSV();
    TempInfo temperatures;
    double saidaControle;
    pid_configura_constantes(5, 1, 5);
    int log=1;

	while(1) {

        readTemperatures(&temperatures);

		pid_atualiza_referencia(temperatures.refTemperature);
		saidaControle = pid_controle(temperatures.intTemperature);
		adjustTemperature(saidaControle);

		temperatures.refTemperature = pid_get_referencia();

        printf("%lf %lf %lf\n",temperatures.intTemperature,
                            temperatures.extTemperature, temperatures.refTemperature);

        writeTemperaturesLCD(temperatures);
        
        if(log){
            appentToLog(temperatures, abs((int)saidaControle));
            log=0;
        }else{
            log = 1;
        }

		alarm(1);
               
	}


    return 0;
}

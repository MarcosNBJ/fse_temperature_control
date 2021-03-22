#include "control_loop.h"

void control_loop(){
  
    TempInfo temperatures;
    double saidaControle;
    int log=1;

	while(1) {

        readTemperatures(&temperatures);

		pid_atualiza_referencia(temperatures.refTemperature);
		saidaControle = pid_controle(temperatures.intTemperature);
		adjustTemperature(saidaControle);

        printToTerminal(temperatures, (int)saidaControle);

        writeTemperaturesLCD(temperatures);
        
        if(log){
            appentToLog(temperatures, (int)saidaControle);
            log=0;
        }else{
            log = 1;
        }

		usleep(800000);
               
	}

}

#include "control_loop.h"

void control_loop(){
    /* 
        Reads the current internal, external and reference temperatures
        then executes PID calculation and finally activates the actuators
    
    */
  
    TempInfo temperatures;
    double saidaControle;
    int log=1; //flag to control whether we should write to log or not

	while(1) {
        
        //reading all temperatures
        readTemperatures(&temperatures);

        //sending reference temperature to PID function
		pid_atualiza_referencia(temperatures.refTemperature);

        //getting PID output and sending it to the control function. Which will turn on/off the fan and resistor
		saidaControle = pid_controle(temperatures.intTemperature);
		adjustTemperature(saidaControle);

        //updating info on ncurses terminal 
        printToTerminal(temperatures, (int)saidaControle);

        //updating info on LCD
        writeTemperaturesLCD(temperatures);
        
        //writing to the log at each two iterations (aprox 2 seconds)
        if(log){
            appentToLog(temperatures, (int)saidaControle);
            log=0;
        }else{
            log = 1;
        }

        //wait for 0.8 seconds, as our UART read takes aprox 0.2 sec
		usleep(800000);
               
	}

}

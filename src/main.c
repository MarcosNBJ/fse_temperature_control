#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "lcd.h"
#include "log.h"
#include "i2c.h"
#include "gpio.h"
#include "pid.h"
#include "quit.h"
#include "control_loop.h"
#include "menu.h"

int main(){
    signal(SIGINT,quit);
    initLCD();
    initI2C();
    initGPIO();
    createCSV();
    pid_configura_constantes(5, 1, 5);

	pthread_t tid[2];
	pthread_create(&tid[0], NULL, (void *) control_loop, (void *) NULL);
	pthread_create(&tid[1], NULL, (void *) menu, (void *) NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);


    return 0;
}

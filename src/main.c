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
#include "quit.h"
#include "control_loop.h"
#include "menu.h"
#include <pthread.h>

int main(){
    signal(SIGINT,quit);
    lcd_init();
    I2C();
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

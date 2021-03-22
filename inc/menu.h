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
#include <ncurses.h>


#ifndef MENU_H_
#define MENU_H_

void menu();
void printToTerminal(TempInfo temp, int controle);
void clear_menu(WINDOW *window);

#endif
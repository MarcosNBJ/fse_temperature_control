#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include "control_loop.h"
#include "temperatures.h"
#include "quit.h"


#ifndef MENU_H_
#define MENU_H_

void menu();
void printToTerminal(TempInfo temp, int controle);
void clear_menu(WINDOW *window);

#endif
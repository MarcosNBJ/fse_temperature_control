#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include "read_data.h"
#include "temperatures.h"
#include "quit.h"


#ifndef MENU_H_
#define MENU_H_

void menu();
void printToTerminal(TempInfo temp, int controle, char *options, int noptions);
void clearWindow(WINDOW *window);

#endif
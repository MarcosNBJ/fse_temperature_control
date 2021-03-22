#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "temperatures.h"

#ifndef LOG_H_
#define LOG_H_

void appentToLog(TempInfo temp, int atuador);
const char *getTimestamp();
void createCSV();

#endif 
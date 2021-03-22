#ifndef LOG_H_
#define LOG_H_
#include "temperatures.h"

void appentToLog(TempInfo temp, int atuador);
const char *getTimestamp();
void createCSV();

#endif 
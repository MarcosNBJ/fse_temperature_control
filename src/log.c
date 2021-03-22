#include "log.h"

const char *getTimestamp(){
    //Returns the current datetime, following the format dd-mm-yyyy-H:M:S

    static char timestamp[20];
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    sprintf(timestamp, "%02d-%02d-%02d-%02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, 
      tm.tm_year + 1900,tm.tm_hour,tm.tm_min,tm.tm_sec);
    return timestamp;
}  

void createCSV() {
  //Creates the log file with header, overwriting if a previous one exists 
  
  FILE *file = fopen("log.csv", "w");
  fprintf(file, "DATETIME, TEMP-INTERNA, TEMP-EXTERNA, TEMP-REFERENCIA, ACIONAMENTO-ATUADOR(%%)\n");
  fclose(file);
}

void appentToLog(TempInfo temp, int atuador) {
  //Receives the temperatures and PID control signal and writes them to log

  FILE *file = fopen("log.csv", "a");
  fprintf(file, "%s,%f,%f,%f,%d\n", getTimestamp(), temp.intTemperature, 
                  temp.extTemperature, temp.refTemperature, atuador);
  fclose(file);
}

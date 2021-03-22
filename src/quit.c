#include "quit.h"

void quit() {
  initLCD();
  setAllOff();
  exit(0);
}
#include "quit.h"

void quit() {
  refresh();
  endwin();
  initLCD();
  setAllOff();
  sleep(1);
  exit(0);
}
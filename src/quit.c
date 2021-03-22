#include "quit.h"

void quit() {
  /*
    Resets ncurses display
    setts LCD, fan and resistor OFF
  */
  refresh();
  endwin();
  initLCD();
  setAllOff();
  sleep(1);
  exit(0);
}
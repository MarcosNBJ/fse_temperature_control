#include "quit.h"

void quit() {
  /*
    Resets ncurses display
    setts LCD, fan and resistor OFF
  */
  
  initLCD();
  setAllOff();
  refresh();
  endwin();
  exit(0);
}

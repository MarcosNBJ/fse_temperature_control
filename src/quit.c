#include "quit.h"

void quit() {
  lcd_init();
  setAllOff();
  exit(0);
}
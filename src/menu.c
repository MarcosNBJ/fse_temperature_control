#include "menu.h"

#define WIDTH 100
#define HEIGHT 20

WINDOW *window;

char *options[] = {
	"Inserir referência manualmente",
	"Pegar referência pelo potenciometro",
	"Sair :(",
};
int ask_reference=0,startx = 0,starty = 0;
int n_options = sizeof(options) / sizeof(char *);

void inputReference() {
  WINDOW *inputWindow;

  float reference;
  int max_height, max_width;
  int _startx, _starty;
  getmaxyx(stdscr, max_height, max_width);

  _starty = (LINES - max_height) / 2;   
  _startx = (COLS - max_width) / 2; 
  refresh();

  inputWindow = newwin(HEIGHT, WIDTH, _starty, _startx);

  wborder(inputWindow, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  mvwprintw(inputWindow, _starty + 1, _startx + 1, "Digite a temperatura desejada, usando ponto como separador: ");

  echo();
  wmove(inputWindow, _starty + 1, _startx + 13);
  wscanw(inputWindow, "%f", &reference);
  
  setUserDefined(reference);

  ask_reference = 0;

  clearWindow(inputWindow);
}

void showMenu(WINDOW *window, int highlight) {
	int x = 2, y = 2, i;

	box(window, 0, 0);
	for(i = 0; i < n_options; i++) {
		if (highlight == i + 1) {
			wattron(window, A_REVERSE);
			mvwprintw(window, y, x, "\t%s", options[i]);
			wattroff(window, A_REVERSE);
		} else {
			mvwprintw(window, y, x, "\t%s", options[i]);
		}
		++y;
	}
	wrefresh(window);
}

void clearWindow(WINDOW *window) {
	wclear(window);
	wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  
	wrefresh(window);
	delwin(window); 
}

void printToTerminal(TempInfo temp, int controle) {
  if (ask_reference == 1)return;

  mvwprintw(window, 6, 1, "\tTEMP INTERNA: %.2f TEMP EXTERNA: %.2f", temp.intTemperature, temp.extTemperature);
  mvwprintw(window, 7, 1, "\tTEMP REFERENCIA: %.2f SINAL DE CONTROLE: %d", temp.refTemperature, controle);
  if(controle > 0){
      mvwprintw(window, 9, 1, "\tRESISTOR: %s","LIGADO");
      mvwprintw(window, 10, 1, "\tFAN: %s", "DESLIGADO");
  }else{
      mvwprintw(window, 9, 1, "\tRESISTOR: %s","DESLIGADO");
      if(controle < -40){
      mvwprintw(window, 10, 1, "\tFAN: %s", "LIGADO");
      }
      else{
          mvwprintw(window, 10, 1, "\tFAN: %s", "DESLIGADO");
      }
  }
  
  wrefresh(window);
}

void menu() {
	int highlight = 1;
	int c;

	initscr();
	start_color(); 
	clear();
	noecho();
	cbreak();
	curs_set(0);
     
	window = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(window, TRUE);
	refresh();
 
	do {
		showMenu(window, highlight);
		c = wgetch(window);

		switch(c) {
			case KEY_UP:
				if(highlight == 1)
					highlight = n_options;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_options)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:    
				if (highlight == 1) {
					clearWindow(window);
                    ask_reference = 1;
                    inputReference();
					window = newwin(HEIGHT, WIDTH, starty, startx);
					keypad(window, TRUE);
					refresh();
				}
				else if (highlight ==2){
					setUserDefined(-1);
				}

				else if (highlight == 3) {
					quit();
				}

				break;
			default:
				refresh();
				break;
		}
	} while(1);
}
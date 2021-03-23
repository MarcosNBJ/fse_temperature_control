#include "menu.h"

#define WIDTH 65
#define HEIGHT 20

WINDOW *window; //main window where everything is displayed
int ask_reference=0; //control variable, used to check if we are on main window or input window

void inputReference() {
  /*
	Window used for the user to input the refeence temperature manually
	
  */
  
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

  mvwprintw(inputWindow, _starty + 1, _startx + 1, "Temperatura: ");

  echo();
  wmove(inputWindow, _starty + 1, _startx + 13);
  wscanw(inputWindow, "%f", &reference);
  
  //sends the user defined temperature to the function responsible for reading data
  // at read_data.c
  setUserDefined(reference);

  ask_reference = 0;

  clearWindow(inputWindow);
}

void showMenu(WINDOW *window, int highlight, char **options, int noptions) {
	/*
	   Displays the options menu
	*/

	int x = 2, y = 2, i;

	box(window, 0, 0);
	for(i = 0; i < noptions; i++) {
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
    //Helper to clear a window 

	wclear(window);
	wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  
	wrefresh(window);
	delwin(window); 
}

void printToTerminal(TempInfo temp, int controle) {
   /*
     Receives temperature info and PID control signal
	 and displays it to ncurses window
  */

  if (ask_reference == 1)return; //does not display when we are at the temperature input screen

  //displaying all temperatures and the value of PID control signal
  mvwprintw(window, 6, 1, "\t---Informacoes em tempo real---");
  mvwprintw(window, 8, 1, "\tTEMP INTERNA: %.2f TEMP EXTERNA: %.2f", temp.intTemperature, temp.extTemperature);
  mvwprintw(window, 9, 1, "\tTEMP REFERENCIA: %.2f SINAL DE CONTROLE: %d", temp.refTemperature, controle);

  //displaying the state of the resistor and fan
  if(controle > 0){
      mvwprintw(window, 11, 1, "\tRESISTOR: %s","LIGADO");
      mvwprintw(window, 12, 1, "\tFAN: %s", "DESLIGADO");
  }else{
      mvwprintw(window, 11, 1, "\tRESISTOR: %s","DESLIGADO");
      if(controle < -40){
      mvwprintw(window, 12, 1, "\tFAN: %s", "LIGADO");
      }
      else{
          mvwprintw(window, 12, 1, "\tFAN: %s", "DESLIGADO");
      }
  }
  
  wrefresh(window);
}

void menu() {

	char *options[] = {
		"Inserir referência manualmente",
		"Pegar referência pelo potenciometro",
		"Sair :(",
	};// All menu options

	int startx = 0,starty = 0;
	int noptions = sizeof(options) / sizeof(char *);
	int highlight = 1;
	int c;

	//initing ncurses display
	initscr();
	start_color(); 
	clear();
	noecho();
	cbreak();
	curs_set(0);
	
	//creating main window
	window = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(window, TRUE);
	refresh();
	
	//infinite loop to show the menu and act based on user choice
	do {
		showMenu(window, highlight, options, noptions);
		c = wgetch(window);

		switch(c) {

			//if key up or down, change what option is highlighted
			case KEY_UP:
				if(highlight == 1)
					highlight = noptions;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == noptions)
					highlight = 1;
				else
					++highlight;
				break;

			case 10: //Value for ENTER key, the user has chosen an option 
				if (highlight == 1) {
					//first option is to enter temperature manually
					clearWindow(window);
                    ask_reference = 1;
                    inputReference();
					window = newwin(HEIGHT, WIDTH, starty, startx);
					keypad(window, TRUE);
					refresh();
				}
				else if (highlight ==2){
					//second option is to define the temperature by potentiometer
					//for that, a -1 is sent to the function responsible for reading data
					//at read_data.c
					setUserDefined(-1);
				}

				else if (highlight == 3) {
					//third option is quit. Calls the function responsible for finishing the program
					quit();
				}

				break;
			default:
				refresh();
				break;
		}
	} while(1);
}

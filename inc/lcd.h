#ifndef LCD_H_
#define LCD_H_
#include "temperatures.h"

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line); //move cursor
void ClrLcd(void); // clr LCD return home
void typeLn(const char *s);
void typeChar(char val);

void selectFirstLine();
void selectSecondLine();
void writeTemperaturesLCD(TempInfo temp);

#endif 
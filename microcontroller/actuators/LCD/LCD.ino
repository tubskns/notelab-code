#include <LiquidCrystal.h>
#include <LcdBarGraph.h>

byte lcd_cols = 16; // -- number of columns in the LCD
byte lcd_line = 2; // -- number of line in the LCD
int contrast = 100;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LcdBarGraph lbg(&lcd, lcd_cols, 0, 1);  //  (&lcd, 16, 0, 1) bargraph length to 16 columns, second row
int max_bar = lcd_cols;

void setup()
{
   analogWrite(6, contrast);
   lcd.begin(lcd_cols, lcd_line);
   delay(100);
   lcd.setCursor(0, 0); // first row
   lcd.print("Notelab");
}
void loop()
{
   lbg.drawValue(random(0, max_bar), max_bar);
   delay(1000);
}
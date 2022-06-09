#include <LiquidCrystal.h>

byte lcd_cols = 16; // number of columns in the LCD
byte lcd_line = 2; // number of line in the LCD
int lcd_contrast = 100;
int lcd_pin = 6;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
   analogWrite(lcd_pin, lcd_contrast);
   lcd.begin(lcd_cols, lcd_line); // set up the LCD's number of columns and rows:
   delay(100);
   lcd.setCursor(0, 0); // first row
   lcd.print("Test message");
   lcd.setCursor(0, 1); // second row
   lcd.print("from NoteLab");
}
void loop()
{

}
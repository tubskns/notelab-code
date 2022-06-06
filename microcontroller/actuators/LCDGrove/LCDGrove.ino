#include <Wire.h>
#include <rgb_lcd.h>

rgb_lcd lcd;

byte lcd_cols = 16; // number of columns in the LCD
byte lcd_rows = 2; // number of rows in the LCD
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

int max_bar = lcd_cols;

void setup() 
{
    lcd.begin(lcd_cols, lcd_rows);
    lcd.setRGB(colorR, colorG, colorB);
    delay(100);
    lcd.setCursor(0, 0); // first row
    lcd.print("Notelab");
    delay(1000);
}
 
void loop() 
{
    lcd.setCursor(0, 1); // second row
    lcd.print(millis()/1000); // number of seconds since reset
    delay(1000);
}

/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int i=0, hes, pokus=0, znak=0, hvez=0;
char heslo[4], sheslo[]="1122"; 
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10, 11}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
            Serial.println(key);
            heslo[hes]=key;
            hes++;
            hvez++;
          }
  if(key=='#')
     { 
           for(int x=0; x<4; x++)
             {
              Serial.print(heslo[x]);
             
              } 
             Serial.println(" ");
           hes=0;    
           hvez=0;
           lcd.clear();
      overeni();
      Serial.println(znak);                   
     }
     hvezd();
   
}

void overeni()
{ znak=0;
  for(int x=0; x<4; x++)
             {
              if(heslo[x]==sheslo[x])
                {
                znak++;
                  }
              } 
              
  }

void hvezd()
{
  lcd.setCursor(0,0);
  for(int x=0; x<hvez; x++)
             {
              lcd.print("*");
             }       
  }  

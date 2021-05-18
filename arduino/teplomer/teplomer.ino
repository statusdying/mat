#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  
#include <OneWire.h> 
#include <DallasTemperature.h>
const int pincidla = 4; 
OneWire owsbernice(pincidla);
DallasTemperature senzor(&owsbernice);
float maxteplota = -100;
float minteplota = 100;

void setup()
{
  lcd.init();
  lcd.backlight();
  senzor.begin();
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
 int teplota;
 

  
 senzor.requestTemperatures(); 
 teplota = senzor.getTempCByIndex(0);
 
 maxmin();
 lcdtest();
 podmin();
 resettlacitko();
/* if(teplota > maxteplota)
 {
  maxteplota = teplota;
  }
  
 if(teplota < minteplota)
 {
  minteplota = teplota;
  }
  */
  
  
 
 
 
/* lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Tep:");
 lcd.setCursor(5,0);
 if(teplota>=0)
 {
  lcd.print("+");
  }else{lcd.print("-");}
 lcd.setCursor(6,0); 
 lcd.print(senzor.getTempCByIndex(0),4);
 lcd.setCursor(14,0); 
 lcd.print((char)223);
 lcd.setCursor(15,0);
 lcd.print("C");
 lcd.setCursor(0,1);*/
 
 /*if(teplota<26.5)
 {
    lcd.print("Topeni - ON");
    analogWrite(10, 255);
    analogWrite(9, 0);
    analogWrite(8, 0);  
    delay(100);  
 }else if(teplota>28.5)
  {          
    lcd.print("klimatizace - ON");
    analogWrite(10, 0);
    analogWrite(9, 0);
    analogWrite(8, 255);  
  }else{          
    analogWrite(10, 0);
    analogWrite(9, 255);
    analogWrite(8, 0);  
  }*/
}
void maxmin()
{
  senzor.requestTemperatures();
  float teplota = senzor.getTempCByIndex(0);
        if(teplota > maxteplota)
       {
        maxteplota = teplota;
        }
        
       if(teplota < minteplota)
       {
        minteplota = teplota;
        }
  Serial.print("Maximalni teplota je: "); 
 Serial.println(maxteplota,4);
 Serial.print("Minimalni teplota je: ");
 Serial.println(minteplota,4);
  }
void podmin()
{
  senzor.requestTemperatures();
  int teplota = senzor.getTempCByIndex(0);
  lcd.setCursor(0,1);
  if(teplota<26.5)
 {
    lcd.print("Topeni - ON");
    analogWrite(10, 255);
    analogWrite(9, 0);
    analogWrite(8, 0);  
    //delay(100);  
 }else if(teplota>28.5)
  {          
    lcd.print("klimatizace - ON");
    analogWrite(10, 0);
    analogWrite(9, 0);
    analogWrite(8, 255);  
  }else{          
    analogWrite(10, 0);
    analogWrite(9, 255);
    analogWrite(8, 0);  
  }
  }

 void lcdtest()
 {
  int teplota = senzor.getTempCByIndex(0);
  lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Tep:");
 lcd.setCursor(5,0);
 if(teplota>=0)
 {
  lcd.print("+");
  }else{lcd.print("-");}
 lcd.setCursor(6,0); 
 lcd.print(senzor.getTempCByIndex(0),4);
 lcd.setCursor(14,0); 
 lcd.print((char)223);
 lcd.setCursor(15,0);
 lcd.print("C");
 lcd.setCursor(0,1);
 }
 
 void resettlacitko()
 {
    if(digitalRead(5)==HIGH)
    {
      maxteplota=-100;
      minteplota=100;
    }
 }
  
  

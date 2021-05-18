#include <Keypad.h>   //deklarace knihoven a proměnných
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD
const byte radky = 4;
const byte sloupce = 4;
char heslo[4];
char heslomain[5] = "1234";
char pin[5]= "1111";
 char klavesa;

char keys[radky][sloupce] = {   //Určení znaků na klávesnici
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'A', 'B', 'C'},
  {'D', 'E', '0', '#'}
};
int o=0;
int n=0;
int i=0;
int x=0;
int pokus=0;
byte pinyRadku[radky] = {5, 4, 3, 2};
byte pinySloupcu[sloupce] = {6, 7, 8, 9};
Keypad klavesnice = Keypad( makeKeymap(keys), pinyRadku, pinySloupcu, radky, sloupce);

void setup() {
   lcd.init();         
  lcd.backlight();
  lcd.home();
}
void loop() {

   if(o==0)  //ve stavu 0 použijeme funkci prihlaseni
   {     
  prihlaseni();
   }
   //stav 1 menu po přihlášení (na rozšíření se pracuje )
   if(o==1){
   lcd.print("                               ");  
   lcd.setCursor(0, 0);
   lcd.print("Zmena hesla- D");    
   lcd.setCursor(0, 1);
   lcd.print("Odhlasit- 0"); 
   klavesa = klavesnice.getKey(); 
   if(klavesa == '0')
   {
    n=0;
    lcd.clear();
    o=0;
    x=0;
    
    }
    else if(klavesa == 'D')
   {
    n=0;
    lcd.clear();
    o=4;
    x=0;
    
    }
    
    
    }
   if(o==3) //stav 3 je pro blokaci (zde používáme funkci zablokovani)
 {
      lcd.print("                               ");
        lcd.setCursor(0, 0);
      lcd.print("Zablokovano");
      zablokovani();
}
// Rozšíření na kterém se pracuje 
/*if(o==4)
 {
   lcd.print("                          ");
  lcd.setCursor(0, 0);
  lcd.print("Stare Heslo:"); 
   klavesa = klavesnice.getKey(); 
if(klavesa && n < 4) {
  lcd.setCursor(n,1);
  lcd.print(klavesa);
  heslo[n]=klavesa;
  n++;
}
if(klavesa == '#' )
  {
for(i=0; i<4; i++)
{
if(heslomain[i]==heslo[i])
{x++;
}


}
  if(x==4)
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Správné heslo");
     delay(2000);
  lcd.clear();
  
    }
    else{
      o=4;
}}} */
}
//Funkce pro prihlaseni 
int prihlaseni(){ 
lcd.print("                          ");
  lcd.setCursor(0, 0);
  lcd.print("Zadejte Heslo:"); 
   klavesa = klavesnice.getKey(); 
if(klavesa && n < 4) {
  lcd.setCursor(n,1);
  lcd.print("*");
  heslo[n]=klavesa;
  n++;
}
if(klavesa == '#' )
  {
for(i=0; i<4; i++)
{
if(heslomain[i]==heslo[i])
{x++;
}}
  if(x==4)
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heslo prijato");
     delay(2000);
  lcd.clear();
  o=1;
    }
    else if(x!=4){
    n=0;
    lcd.clear();
    o=0;
    x=0;
    pokus=pokus+1;
     lcd.setCursor(0, 0);
    lcd.print("Chyba. pokus:");
    lcd.print(pokus);
    delay(1000);
    
    if(pokus==3)
    {n=0;
    x=0;
      o=3;
}}}}
//funkce slouzi pro zablokovani 
int zablokovani(){  
   klavesa = klavesnice.getKey(); 
if(klavesa && n < 4) {
  lcd.setCursor(n,1);
  lcd.print('#');
  heslo[n]=klavesa;
  n++;
}
if(klavesa == '#' )
  {
for(i=0; i<4; i++)
{
if(pin[i]==heslo[i])
{x++;
}
}
  if(x==4)
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PIN PRIJAT");
     delay(2000);
  lcd.clear();
  o=0;
  n=0;
  x=0;
  pokus=0;
   }
  }
 }
   
  







  

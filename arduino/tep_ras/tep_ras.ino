#include <LiquidCrystal_I2C.h>     // knihovna pro LCD
#include <Wire.h>                 // knihovna pro I2C komunikaci

  //knihovny pro praci se senzorem
#include <OneWire.h>
#include <DallasTemperature.h>

  //na pinu 2 je pripojen vodic data od teplot. snimace
const int pinsenzor = 2;   //muzeme pouzit hstg define pinsenzor 2
  //komikace s Onewire zarizeni s knihovnou OneWire
OneWire ds(pinsenzor);

  // propojeni senzoru s Dallas temperature knihovnou
DallasTemperature senzor(&ds);

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); //definice LCD displeje

  //piny od rgb led pro barvy
int red = 9; 
int green = 10;
int blue = 11;

  //teploty snimane senzorem
float nvyssTep = 0.0;
float nnizTep = 0.0;
float teplotaC = 0.0;

 byte Lpiny[] = {  A0, 8, 7, 6, 5, 4, 3, A1}; //led pro lsb
 
void setup() {
  
  lcd.init();              //inicializuje displej
  lcd.backlight();        //podsviceni
  
 Serial.begin(9600);     //seriovy displej

 senzor.begin();       //senzor
  
 lcd.setCursor(0,0);
 lcd.print("Teplota: ");                  //vypis na lcd, text ktery se nemeni

senzor.requestTemperatures();           //ukladani "brani" teploty ze senzoru
teplotaC = senzor.getTempCByIndex(0);  //ukladani ve float (.0),ByIndex() se pouziva pri vice cidlech na 1 datovem pinu, cislem v zavorce je prepiname

  nvyssTep = teplotaC;
  nnizTep = teplotaC;

 teplotanorm(teplotaC);   //void pro vypis prubezne teploty

 nejvyssiC(nvyssTep);    //void pro vypis max. teploty

 nejnizsiC(nnizTep);     //void pro vypis min. teploty

 pinMode(red, OUTPUT);
 pinMode(green, OUTPUT); //rgb
 pinMode(blue, OUTPUT);

 
for(int x = 0; x < 8; x++) {
    pinMode(Lpiny[x], OUTPUT);
  }
}

void loop() {

  byte i;
  byte p = 0;

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      return;
  }
  Serial.println();

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        

  delay(1000);   

  p = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         
  
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           //9 bytes, 0-LSB, 1-MSB,..
    data[i] = ds.read();
    }
  Serial.print("LSB registr:");     //vypis LSB registru na ser. monitor
  Serial.println(data[0], BIN);
  Serial.print(" ");
  

    for (int i =0;i<8;i++)    //LSB na ledkach
  {
    if (bitRead(data[0], i)==1)
    {
      digitalWrite(Lpiny[i], HIGH);
    }
    else
    {
      digitalWrite(Lpiny[i], LOW);
    }
  }

 
senzor.requestTemperatures();   
teplotaC = senzor.getTempCByIndex(0);   
teplotanorm(teplotaC);           //prubezna teplota
 
if(teplotaC > nvyssTep)          //max. teplota
  {
     nvyssTep = teplotaC;
      
  }
  nejvyssiC(nvyssTep);  
if(teplotaC < nnizTep)          //min. teplota
  {
    nnizTep = teplotaC;
   
  }
 nejnizsiC(nnizTep);


  if(teplotaC<26.5)               //kdyz klesne teplota pod 26,5 stupnu tak vypise o zapnuti topeni
   {
   lcd.setCursor(9, 0);
   lcd.print("zapni");
   lcd.setCursor(10, 1);
    lcd.print("topeni");
 RGB_barva(255, 0, 0);            // cervena, rgb znaci cervenou ze se ma zapnout topeni
    }
 
    if(teplotaC>28.5)            //kdyz vypise teplotu vyssi nez 28,5 stupnu tak vypise o zapnuti klimy
    {
    lcd.setCursor(9, 0);
    lcd.print("zapni");
    lcd.setCursor(10, 1);
    lcd.print("klimu  ");
   RGB_barva(0, 0, 255);        // modra, rgb znaci modrou, ze se ma zapnout klima
    }

    if((teplotaC>=26.5)&&(teplotaC<=28.5))   //pri normalni teplote 26,5 C - 28,5 C
    { 
    lcd.setCursor(9, 0);
    lcd.print("            ");
    lcd.setCursor(10, 1);
    lcd.print("          ");
    RGB_barva(0, 255, 0);    // zelena, rgb znaci ze teplota je v klidu
    } 
    delay(1000);            // 1s
}

void nejnizsiC(float n)                  //void pro min. teplotu- vypis na seriovy monitor
{
  Serial.print("  Nejnizsi teplota: ");
  Serial.print(n, 4);                   //4 desetinna mista
   Serial.print(" \xC2\xB0");           // znak celsia
 Serial.print("C|");                    //vypis seriovy monitor
}

void nejvyssiC(float m)                //void pro max. teplotu- vypis na seriovy monitor
{
  Serial.print("   Nejvyssi teplota: ");
  Serial.print(m, 4);                 //4 desetinna mista
   Serial.print(" \xC2\xB0");         // znak celsia
 Serial.print("C|");                 //vypis seriovy monitor 
}

void teplotanorm(float x)               //void pro prubezne namerenou teplotu- vypisuje na lcd displej
{
lcd.setCursor(0,1);
 lcd.print(x, 4);                     //vypis na lcd displej, 4 desetinna mista
 lcd.print((char)223);                //znak pro celsia na lcd
 lcd.print("C");
}

void RGB_barva(int red_value, int green_value, int blue_value)    //void pro rgb led
{
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}

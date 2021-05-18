
//Takže pro začátek, nejjednoduší způsob jak vyřešit základní deklaraci klávesnice je zajít do "Soubor" --> "Příklady(examples)" --> "Keypad" --> "Hello keypad"
//Zbytek programu je popsán postupně, doporučil bych číst každý komentář, aby se předešlo chybám, je to +- stručné

//"Doufám že to bude helpful" - Fico making this at 2AM before school

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27,16,2); //musí se určit podle vlastního připravku - v poznámkách dole nechám celý program na zjištění typu lcd v komentáři


const byte ROWS = 4; //four rows  //řady a sloupce upravíme podle klávesnice 
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {  //deklarujeme podle vlastní klávesnice, podle toho upravíme i piny, stačí si s tím vyhrát a pomocí postupně testovat a zjisit jak jste to zapojili
                           // |                                                                                                //if (key){
                           // |                                                                                                //Serial.println(key);}
  {'1','2','3','A'},       // |
  {'4','5','6','B'},       // |         
  {'7','8','9','C'},       // | 
  {'*','0','#','D'}        // ˇ 
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 7, 6}; //connect to the column pinouts of the keypad

char heslo[4] ;  //heslo do kterého zapisujeme, musíme určit velikost
char odem[] ="1234";  //heslo na odemykání
char sheslo[] ="5555"; //servisní heslo
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 char key = keypad.getKey(); //pro zjíšťování kláves

 int i=0; //i - stav který používáme pro určování kolik potřebujem znaků, podle toho pracujeme s výpisem atd
int s=0; // s - počet správných čísel v hesle které se porovnává, otevře se pouze když je celé heslo stejné
int z=0; // z - stav který se nám otevře jakmile namačkáme 4 hodnoty a potvrdíme # a pustí nás ke kontrole 
int hvezda=-1;  // hvezda - proměnná pro hvězdičku, která určuje jen její pozici při výpisu, musí být -1 protože jinak blbne
int hp=3;  // hp - počet pokusů, pokud klesne na 0 je nutno zadat servisní heslo
void setup(){
 
  Serial.begin(9600); //Deklarace sériových monitorů
  lcd.init(); // lcd.init nebo lcd.begin podle typu liquid_crystal knihovny
  lcd.backlight();
}
  
void loop(){
key = keypad.getKey();
  
 if(hp>0){  //pokud jsou pokusy větší než 0, celý program může jet 
if(z==0){   
  if(i==0){
    lcd.setCursor(0,0);  //nutno zadat lcd.setCursor jinak se to vypíše přes celé LCD 
    lcd.print("Zadej heslo");
  
    }
   else if(i>0){   //pokud je i>0 tak zapisujeme na LCD ale vypisujeme jen *
        lcd.setCursor(0,0);
        lcd.print("Zadej heslo");
        lcd.setCursor(hvezda,1);
        lcd.print("*");
      }
    if(i<4){  //dokud není i<= 4 tak postupně zapisujeme do proměnné "heslo" - i<4 je protože se to zastaví na 4 a my požadujeme 4 číselný kód, automaticky po 4 se vypne tento if, tímpádem nemůžeme zadat víc čísel
      if (key){
    Serial.println(key);
    heslo[i]=key;
    i++;
    hvezda++;
  
  }
      
      }
   porovnavani(); //funkce kde se porovnává heslo s heslem na odemykání
 }
    
 else if(z==1){  //zde se přepneme na stav z==1, kde se vybírá mezi odemknutím a špatným pokusem podle zadaného hesla
 
        if(s==4){ //pokud je celé heslo správně
         
          odemknut();
          }
        else if(s!=4){ //pokud není celé heslo správně
      
          spatny();
          }
    
    
    }
    
  }
  else if(hp==0){ //pokud dojdou pokusy
    servisni();
    }
  
 /* if (key){
    Serial.println(key); //pouze pro zjištění a výpisu hodnot na sériový display, hodí se využívat při testování klávesnice postupně
  }

 */

  
}

void odemknut(){
 
  lcd.print("Odemknuto");
  lcd.setCursor(0,1);
  lcd.print("Pro zamceni =A   ");

  
  if(key == 'A'){ //na přepnutí z5 do hlavního programu
    i=0;
    s=0;
    z=0;
    hvezda=-1; //všechy hodnoty se musí vynulovat pro správnou funkci programu
    lcd.clear();
    }
    
    

  
  }

void spatny(){
 lcd.clear();
  lcd.print("Spatny pokus");
  lcd.setCursor(0,1);
  lcd.print("zivoty=");
     hp--;
  lcd.print(hp);
    z=0;  //výpis pokůsů s automatickým návratem do programu, POZOR!! odečet pokusů musí být před výpisem, jinak by to vypisovalo vždy hp+1;
    i=0;
    s=0;
 

    hvezda=-1;
    delay(2000);
    lcd.clear();
  
  
  }

 void porovnavani(){
   if(i==4 && key == '#'){ //porovnávání, pokud i==4 (což znamená že jsme dosáhli požadované délky kódu) a pokud zmáčkneme #
  for(i=0;i<4;i++){

    if(heslo[i] == odem[i])
    {
      s++; //porovnávání postupně
      }
      lcd.clear();
    z=1; //překlopení do stavu kde se vyhodnocuje jestli heslo bylo správné nebo ne
    }}
  }

 void servisni(){
  if(z==0){  //víceméně stejný postup jako ve "void loop" ale je lepší to napsat do funkce aby loop nebyl tak dlouhý
if(i==0){
    lcd.setCursor(0,0);
    lcd.print("Zadej servisni");
  
    }
   else if(i>0){
        lcd.setCursor(0,0);
        lcd.print("Zadej servisni");
        lcd.setCursor(hvezda,1);
        lcd.print("*");
      }
    if(i<4){
      if (key){
    Serial.println(key);
    heslo[i]=key;
    i++;
    hvezda++;
  
  }}
  if(i==4 && key == '#'){
  for(i=0;i<4;i++){

    if(heslo[i] == sheslo[i]) //jsou zde 2 rozdíly, kontroluje se zde servisní heslo
    {
      s++;
      }
      lcd.clear();
    z=1;
    }}
    }
    
 else if(z==1){
  if(s==4){  //zde se program ustálí znova do normálu, vyresetujou se všechny proměnné společně s pokusy
    hp=3;
    
    i=0;
    s=0;
    z=0;
    hvezda=-1;
    }
    else if(s!=4){  //a druhý rozdíl je že zde není počet pokusů, takže se to resetuje do té doby, dokud nezadáte správné servisní heslo, je to takový cheesy způsob ale hej, v zadání není řečeno jinak takže ez
    i=0;
    s=0;
    hvezda=-1;
      
      }
  } }
  
  
/* LCD 
 #include <Wire.h>
 
 
void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}
 */


/*
 .
,, ━━━━-╮
╰┃ ┣▇━▇
 ┃ ┃  ╰━▅╮
 ╰┳╯ ╰━━┳╯G G
  ╰╮ ┳━━╯T Y 4 
 ▕▔▋ ╰╮╭━╮ T U T O R I A L
╱▔╲▋╰━┻┻╮╲╱▔▔▔╲
▏Fiat  ▔▔Punto▔  O O┃
╲╱▔╲▂▂▂▂╱▔╲▂▂▂╱
 ▏╳▕▇▇▕ ▏╳▕▇▇▕
 ╲▂╱╲▂╱ ╲▂╱╲▂

 */
 

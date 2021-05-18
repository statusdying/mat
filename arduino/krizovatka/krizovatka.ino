const int pinSPI = 2;
const int pinC1 = 11;
const int pinO1 = 10;  
const int pinZ1 = 9;

const int pinC2 = 8;
const int pinO2 = 7;  
const int pinZ2 = 6;

const int pinCHZ1 = 13;
const int pinCHZ2 = 12;
const int pinCHC1 = 4;
const int pinCHC2 = 5;

int x = 1;
void setup()
{
  pinMode(pinSPI, INPUT);
  pinMode(pinC1, OUTPUT);
  pinMode(pinO1, OUTPUT);
  pinMode(pinZ1, OUTPUT);
  pinMode(pinC2, OUTPUT);
  pinMode(pinO2, OUTPUT);
  pinMode(pinZ2, OUTPUT);
}

void loop()
{  
  if(x==0 && digitalRead(pinSPI)==1)
     { 
     x=1;
      digitalWrite(pinC1, HIGH);
        digitalWrite(pinC2, HIGH);
        digitalWrite(pinZ1, LOW);
        digitalWrite(pinZ2, LOW);
        digitalWrite(pinO1, LOW);
        digitalWrite(pinO2, LOW);
        delay(2000);
       
     }else if(x==1 && digitalRead(pinSPI)==0) 
       {x=0;
        
         }
  switch (digitalRead(pinSPI)) 
  {
    case 1:
       den();
    break;
  
    case 0:
       noc();
    break;  
  } 
}

void den()
{ 
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinO2, HIGH);
  delay(500);
  digitalWrite(pinO2, LOW);
  digitalWrite(pinC2, LOW);
  digitalWrite(pinZ2, HIGH);
  digitalWrite(pinCHC1, LOW);
  digitalWrite(pinCHZ1, HIGH);
  
  delay(1000);
  digitalWrite(pinCHZ1, LOW);
  digitalWrite(pinCHC1, HIGH);
  digitalWrite(pinZ2, LOW);
  digitalWrite(pinO2, HIGH);
  delay(500);
  digitalWrite(pinO2, LOW);
  digitalWrite(pinC2, HIGH);
  delay(500);
  digitalWrite(pinO1, HIGH);
  delay(500);
  digitalWrite(pinO1, LOW);
  digitalWrite(pinC1, LOW);
  digitalWrite(pinZ1, HIGH);
  digitalWrite(pinCHC2, LOW);
  digitalWrite(pinCHZ2, HIGH);
  delay(500);
  digitalWrite(pinCHZ2, LOW);
  digitalWrite(pinCHC2, HIGH);
  digitalWrite(pinZ1, LOW);
  digitalWrite(pinO1, HIGH);
  delay(500);
  digitalWrite(pinO1, LOW);
    
}

void noc()
{   
    digitalWrite(pinCHZ1, LOW);
    digitalWrite(pinCHC1, LOW);
  digitalWrite(pinCHZ2, LOW);
  digitalWrite(pinCHC2, LOW);
  digitalWrite(pinC1, LOW);
    digitalWrite(pinC2, LOW);
    digitalWrite(pinZ1, LOW);
    digitalWrite(pinZ2, LOW);
    digitalWrite(pinO1, HIGH);
  digitalWrite(pinO2, HIGH);
    delay(500);
    digitalWrite(pinO1, LOW);
    digitalWrite(pinO2, LOW);
    delay(500);
    

}

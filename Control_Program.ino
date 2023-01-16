
#include <Servo.h>
#include <ChainableLED.h>
#define NUM_LEDS  1
const int IN1 = A0;
const int IN2 = A1; 
const int IN3 = A2; 
const int IN4 = A3;
const int ENA = 5;
const int ENB = 6;
const int rgb_pwr = 12;
const int clk_pin = 6;
const int data_pin = 5; 
int pozycja = 90;
int command = 0;
int skan=1;
Servo serwomechanizm;
int LSensorPin = 7;
int RSensorPin = 8;
int dystans = 0;
int PSensor;
int TSensor;   
const int TRIG = 11; 
const int ECHO = 12;
int i =0; 
int j=0;
ChainableLED leds(clk_pin, data_pin, rgb_pwr, NUM_LEDS);
void Test_dystansu()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  float czas = pulseIn(ECHO, HIGH);
  dystans = czas / 58;                
  if ((dystans<=15)&&(PSensor==LOW)&&(TSensor==HIGH))
  {
   Serial.println("Przed!!!");
  }

  else if ((dystans>15)&&(PSensor==LOW)&&(TSensor==HIGH))
  {
//    Serial.println("daleko przeszkoda");
    }
  if (PSensor==HIGH)
    {
      Serial.println("Spadek!!!");
    }
  if (TSensor==LOW)
    {
      Serial.println("Z tyłu!!! ");
    }
}  
void KonfiguracjaUltradzwieku()
{
  pinMode(ECHO, INPUT); 
  pinMode(TRIG, OUTPUT); 
}

void KonfiguracjaOdbicia()
{
  pinMode(RSensorPin, INPUT);
  pinMode(LSensorPin, INPUT);
}
void setup() { 
serwomechanizm.attach(9); 
void KonfiguracjaOdbicia();
pinMode (IN1, OUTPUT); 
pinMode (IN2, OUTPUT); 
pinMode (IN3, OUTPUT); 
pinMode (IN4, OUTPUT); 
pinMode (ENA, OUTPUT); 
pinMode (ENB, OUTPUT);
KonfiguracjaUltradzwieku();
Serial.begin(9600);
}
void loop() 
{

if (Serial.available() > 0)
  { command=Serial.read();

  } 

  i=0;
  j=0;
  TSensor = digitalRead(RSensorPin);          
  PSensor = digitalRead(LSensorPin);
  Test_dystansu();
if (command == '0')
  {
digitalWrite(IN1, HIGH); 
digitalWrite(IN2, LOW); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, HIGH); 
analogWrite(ENA, 230); 
analogWrite(ENB, 230);
command= 0;
  } 
else if(command == '1')
{ digitalWrite(IN1, LOW); 
digitalWrite(IN2, HIGH); 
digitalWrite(IN3, HIGH); 
digitalWrite(IN4, LOW); 
analogWrite(ENA, 230); 
analogWrite(ENB, 230); 
command=0;
} 
else if (command == '2')
{ digitalWrite(IN1, HIGH); 
digitalWrite(IN2, LOW); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, LOW); 
analogWrite(ENA, 230); 
analogWrite(ENB, 230); 
command=0; 
} 
else if (command == '3')
{ digitalWrite(IN1, LOW); 
digitalWrite(IN2, LOW); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, HIGH); 
analogWrite(ENA, 230); 
analogWrite(ENB, 230); 
command=0;
} 
else if (command == '8')
{ digitalWrite(IN1, HIGH); 
digitalWrite(IN2, LOW); 
digitalWrite(IN3, HIGH); 
digitalWrite(IN4, LOW); 
analogWrite(ENA, 230); 
analogWrite(ENB, 230); 
command=0;
} 
else if (command == '7')
{ digitalWrite(IN1, LOW); 
digitalWrite(IN2, HIGH); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, HIGH); 
analogWrite(ENA, 230); 
analogWrite(ENB, 230); 
command=0;
} 

else if ((command == '4') or (TSensor == LOW) or  (PSensor == HIGH) or  (dystans<=12))
{ digitalWrite(IN1, HIGH); 
digitalWrite(IN2, HIGH); 
digitalWrite(IN3, HIGH); 
digitalWrite(IN4, HIGH);
delay(100); 
while (((dystans<=15) &&(i<5)) or ((PSensor == HIGH) && (i<5)))
{
  leds.setColorHSB(0,0 , 1.0, 0.5);
  digitalWrite(IN1, LOW); 
digitalWrite(IN2, HIGH); 
digitalWrite(IN3, HIGH); 
digitalWrite(IN4, LOW); 
analogWrite(ENA, 230); 
analogWrite(ENB, 230); 
i=i+1;
delay(50);
  }
  while((TSensor == LOW)&&(j<5))
  {
    leds.setColorHSB(0,0 , 1.0, 0.5);
  digitalWrite(IN1, HIGH); 
digitalWrite(IN2, LOW); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, HIGH); 
analogWrite(ENA, 230); 
analogWrite(ENB, 230);
j=j+1;
delay(50);    
  }
  leds.setColorHSB(0,0.5 , 1.0, 0.5);
  digitalWrite(IN1, HIGH); 
digitalWrite(IN2, HIGH); 
digitalWrite(IN3, HIGH); 
digitalWrite(IN4, HIGH); 
} 
else if (command == '5') {
  pozycja=180;
  serwomechanizm.write(pozycja);
delay(100);
while (pozycja==180 && skan<11)
{
 Test_dystansu();
skan=skan+1;
delay(100);
}
pozycja=90;
serwomechanizm.write(pozycja);
delay(1000);
Test_dystansu();
skan=0;
command= 0;
}
else if (command == '6') {
  pozycja=0;
serwomechanizm.write(pozycja);
delay(100);
while (pozycja==0 && skan<11)
{
 Test_dystansu();
skan=skan+1;
delay(100);
}
pozycja=90;
serwomechanizm.write(pozycja);
delay(1000);
Test_dystansu();
skan=0;
command= 0;
}
}

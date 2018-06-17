
// include library 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define Wire Wire1
// declairing LCD address 
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Sensor constants and parameters
const float VRefer = 2.6;       // voltage of adc reference
const int pinAdc   = A8;
// I/O pin declaration 
int switch1 = A2; // pin for setpoint 1
int switch2 = A3; //pin for setpoint 2
int fan1 = 49; //output pin for maximum voltage 5V
int fan2 = 51; // output pin for lower speed using 3.3 v
  int i=1;
///////////////////////////////////////////////////////
void setup() 
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    lcd.init();
  lcd.backlight();// initializing lcd backllight and etc
  lcd.print("sensor readings");// print message to the screen
  delay(10000);// delaying the void loop
  lcd.clear();
 
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);

}

void loop() 
{

   
     if (analogRead((switch2)||(analogRead(switch1)))>0.5){
        //when setpoint is 5%
        setpoints();
        }
        
        
}

///////////////////////////////////////////////////////////////////////////
float readO2Vout() // reads the output voltage of the Groove oxygen sensor 
{
    long sum = 0;
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pinAdc);
    }
    sum >>= 5;
    float MeasuredVout = sum * (VRefer / 1023.0);
return MeasuredVout;
}
/////////////////////////////////////////////////////////////////////////
float readConcentration(){ // converts read voltage to oxygen concentration
    float MeasuredVout = readO2Vout();
    float Concentration = MeasuredVout * 0.21 / 2.0;
    float Concentration_Percentage=Concentration*100;
return Concentration_Percentage;
}

//////////////////////////////////////////////////////////////////////
void setpoints()// for setpoint equal 5%
{  
 float Vout = readO2Vout();
float o=readConcentration(); //reads the current oxygen concengration
if (analogRead(switch2)>0){
  while ((o>7.0)&&(o<21)){
    digitalWrite(fan1,LOW);
    digitalWrite(fan2, HIGH);
  lcd.setCursor(2,0);
    lcd.clear();
    lcd.print("setpoint 7%");
    lcd.setCursor(2,0);
    lcd.print("ox%:");
    lcd.print(o);
    Serial.println(o);
    delay(1000);
    o=readConcentration();
 
  
    }
    while ((o>=6.9)&&(o<7.1)){
  digitalWrite(fan1,LOW);
  digitalWrite(fan2, HIGH);
  delay(5000);
  digitalWrite(fan1,HIGH);
  digitalWrite(fan2, HIGH);
 delay(5000);
 o=readConcentration();
    lcd.setCursor(2,0);
    lcd.clear();
    lcd.print("setpoint 7%");
    lcd.setCursor(2,1);
    lcd.print("ox%:");
    lcd.print(o);;
    Serial.println(o);
    delay(1000); 
    }
    while (o<6.89){
  digitalWrite(fan1,HIGH);
  digitalWrite(fan2, HIGH);
  o=readConcentration();
 Serial.println(o);
  lcd.setCursor(2,0);
    lcd.clear();
    lcd.print("setpoint 5%");
    lcd.setCursor(2,1);
    lcd.print("ox%:");
    lcd.print(o);
    Serial.println(o);
    delay(1000);
   
 
        }
  }
  
    if (analogRead(switch1)>0){
  while ((o>5.0)&&(o<21)){
    digitalWrite(fan1,LOW);
    digitalWrite(fan2, HIGH);
  lcd.setCursor(2,0);
    lcd.clear();
    lcd.print("setpoint 5%");
    lcd.setCursor(2,0);
    lcd.print("ox%:");
    lcd.print(o);
    Serial.println(o);
    delay(1000);
    o=readConcentration();
  
    } 
        while ((o>=4.9)&&(o<5.1)){
  digitalWrite(fan1,LOW);
  digitalWrite(fan2, HIGH);
  delay(5000);
  digitalWrite(fan1,HIGH);
  digitalWrite(fan2, HIGH);
 delay(5000);
 o=readConcentration();
    lcd.setCursor(2,0);
    lcd.clear();
    lcd.print("setpoint 5%");
    lcd.setCursor(2,1);
    lcd.print("ox%:");
    lcd.print(o);;
    Serial.println(o);
    delay(1000); 
    }
    while (o<4.89){
  digitalWrite(fan1,HIGH);
  digitalWrite(fan2, HIGH);
  o=readConcentration();
 Serial.println(o);
  lcd.setCursor(2,0);
    lcd.clear();
    lcd.print("setpoint 5%");
    lcd.setCursor(2,1);
    lcd.print("ox%:");
    lcd.print(o);
    Serial.println(o);
    delay(1000);
  } }
  }



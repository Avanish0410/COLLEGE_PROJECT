/*
  Added features integrated sensors with Arduino UNO
  Telnet port 23
  Maintained by:-Avanish Gupta
  Email ID:-avanishgupta355@gmail.com
  Developed code for College project
*/

#include <LiquidCrystal.h>  //LiduidCrystalDisplay Library
#include <esp_wifi.h>     //Esp32 Library 
#include <string.h>

const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;

LiquidCrystal lcd(12,11,5,4,3,2);

const int8_t lm35_pin=A1;

int16_t temp_adc_val;         //declares varibles names
int temp_val;
const int analogInPin=A0;
const int relay=6;
const int buzzer=7;
const int sensor=8;
int buttonState=0;
int sensorValue=0;

void setup()
{
delay(4000);
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("IOT Based Indstl");
lcd.setCursor(0,1);
lcd.print("protection System");
delay(1000);

Serial.begin(9600);        //baud rate
pinMode(relay,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(sensor,INPUT);
digitalWrite(relay,LOW);
digitalWrite(buzzer,LOW);

Serial.printIn("ATE0\r\n");   //text mode
delay(1000);
Serial.printIn("AT+CWMODE_DEF=2\r\n");
delay(1000);
Serial.printIn("AT+CIPMUX=1\r\n");
delay(1000);
Serial.printIn("AT+CIPSERVER=1,80\r\n");
delay(1000);
}
void loop()
{
buttonState=digitalRead(sensor);
if(buttonState==LOW)
{
digitalWrite(buzzer,HIGH);
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("Fire Detected");
delay(1000);
Serial.printIn("AT+CIPSEND=0,20\r\n");      // AT Command for Communication Module
delay(1000);
Serial.print("Fire Detected--------");
delay(1000);
}
else
{
digitalWrite(buzzer,LOW);
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("No Fire Detected");
delay(1000);
Serial.printIn("AT+CIPSEND=0,22\r\n");
delay(1000);
Serial.print("No Fire Detected--------");
delay(1000);
}
sensorValue=analogRead(analogInPin);
if(sensorValue<100)
{
 digitalWrite(relay,LOW);  //turn the LED off by making the voltage LOW
 lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print(sensorValue);
 lcd.print("Gas Detected");
 delay(1000);

 serial.println("AT+CIPSEND=0,20\r\n");
 delay(1000);
 Serial.print("Gas detected--------");
 delay(1000);
}

else
{
  digitalWrite(relay, HIGH);  //turn the LED on (HIGH is the voltage level)
  lcd.begin (16,2);
  lcd.SetCursor(0,0);
  lcd.print(sensorValue);
  lcd.print("No Gas Dtctd");
  delay(1000);
  
  Serial.println("AT+CIPSEND=0,20\r\n");
  delay(1000);
  Serial.print("NO Gas detected-------");


}

delay(20);   //take a break

/////////

temp_adc_val=analogRead(lm35_pin);   //REad temperature from LM35
//temp_val=(temp_adc_val * 4.88);
//temp_val=(temp_val/10);
//temp_val=(temp_val+45);
 delay(500);

 Serial.println("AT+CIPSEND=016,\r\n");
 delay(500);
Serial.print("Temp(degC):");
Serial.print(temp_adc_val);
Sreial.print(" ");
delay(2000);

lcd.setCursor(0,0);
delay(500);
lcd.print("Temp(degC):");
lcd.print(temp_adc_val);

delay(2000);
lcd.clear();
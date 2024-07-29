const int pingPin =A2; // Trigger Pin of Ultrasonic Sensor
const int echoPin =A3; // Echo Pin of Ultrasonic Sensor
long duration;
int distance;
#include "DHT.h"
#include <LiquidCrystal.h>
//#include <SoftwareSerial.h>
//SoftwareSerial wifi(9,10);
const int rs =8, en =9, d4 =10, d5 =11, d6 =12, d7 =13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DHTPIN 7    
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int ss=A0;
int obj=A1;
int buz=3;
int light=A5;
int fan=6;
int f=A4;
int mot=5;
int mot1=4;
int ef=2;
void setup() {
  Serial.begin(115200);
//  wifi.begin(115200);
  pinMode(f,INPUT);
  pinMode(obj,INPUT);
  pinMode(mot,OUTPUT);
  pinMode(ef,OUTPUT);
  pinMode(mot1,OUTPUT);
  pinMode(pingPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(light,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(ss,INPUT);
  pinMode(buz,OUTPUT);
  digitalWrite(light,1);
  digitalWrite(fan,0);
  digitalWrite(mot,0);
  digitalWrite(mot1,0);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("WELCOME");
  wifi_init();
}
void loop() {
  delay(2000);
  digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= (duration/2)/29.1;
int h = dht.readHumidity();
int t = dht.readTemperature();
int sval=analogRead(ss)/1.2;
int fval=digitalRead(f);
int oval=digitalRead(obj);
 //Serial.println("T:"+ String(t) + "  H:" +String(h) + "  S:" + String(sval));
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("T:" + String(t) + "  H:" +String(h)+ " L:" +String(distance));
 lcd.setCursor(0,1);
 lcd.print("G:" + String(sval)+  "  F:" +String(fval)+  " O:" +String(oval));
 upload_iot(t,h,sval,fval,distance);
if(sval>350)
{
  digitalWrite(ef,1);
}
else
{
  digitalWrite(ef,0);
}
if(sval>35 0 || fval==0)
 {
  digitalWrite(buz,1);
 }
 else
 {
  digitalWrite(buz,0);
 }
 if(distance>10)
{
  analogWrite(mot,100);
}
else
{
  digitalWrite(mot,0);
}
if(oval==0)
{
  digitalWrite(light,0);
}
else
{
  digitalWrite(light,1);
}
 if(t>30 && t<35)
 {
  analogWrite(fan,100);
 }
 else if(t>35 && t<40)
 {
  analogWrite(fan,150);
 }
  else if(t>40)
 {
  analogWrite(fan,250);
 }
 else
 {
  digitalWrite(fan,0);
 }  
}
void wifi_init()
 {
   Serial.println("AT+RST");
  delay(2000);
  Serial.println("AT+CWMODE=1");
  delay(1000);
  Serial.print("AT+CWJAP=");
  Serial.write('"');
  Serial.print("Oppo"); // ssid/user name
  Serial.write('"');
  Serial.write(',');
  Serial.write('"');
  Serial.print("00000000"); //password
  Serial.write('"');
  Serial.println();
  delay(1000);
 }

void upload_iot(int x,int y,int z, int p,int q) //ldr copied int to - x   and gas copied into -y
{
  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  Serial.println(cmd);
  delay(1500);

 String getStr ="GET /update?api_key=1E636036B6WCF40K&field1=";
  getStr += String(x);
  getStr +="&field2=";
  getStr += String(y);
  getStr +="&field3=";
  getStr += String(z);
  getStr +="&field4=";
  getStr += String(p);
  getStr +="&field5=";
  getStr += String(q);
  getStr += "\r\n\r\n";
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  Serial.println(cmd);
   delay(1500);
  Serial.println(getStr);
  delay(1500);
}

#define IN1 3  //定义IN1为3口
#define IN2 4 
#define IN4 5
#define IN3 6//定义IN2为4口
#define  ENA  10
#define  ENB  9//定义ENA为10口
#define  PIN  13
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //引用I2C库
LiquidCrystal_I2C lcd(0x27,16,2); 
int measurePin = A3;            
int ledPower = 12;            
#include <dht11.h>
 
dht11 DHT11;
#define PIN_DHT11 8
   
 
unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;
 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  lcd.init();                  // 初始化LCD
  lcd.backlight(); 
  pinMode(IN1,OUTPUT);//设置输出
 pinMode(IN2,OUTPUT);
 pinMode(ENA,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 pinMode(ENB,OUTPUT);//设置LCD背景等亮
 pinMode(13,OUTPUT);
}
 
void loop(){
   DHT11.read(PIN_DHT11);
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(measurePin);
 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);
 
  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;
 
  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }
 
  lcd.setCursor(0,0);                //设置显示指针
  lcd.print("DD:");     //输出字符到LCD1602上
  lcd.setCursor(3,0);
  lcd.print(dustDensity);
  lcd.setCursor(8,0);
  lcd.print("Hum:");
  lcd.setCursor(12,0);
  char hum[4];
  sprintf(hum,"%3d%%",DHT11.humidity);
  lcd.print(hum);
  lcd.setCursor(0,1);
  lcd.print("Tem:");
  lcd.setCursor(4,1);
  char tem[4];
  sprintf(tem,"%d'C",DHT11.temperature);
  lcd.print(tem);
  delay(1000);
 
  while(Serial.available())
   {
     char c=Serial.read();
     switch (c)
     {
     case 'H': 
      {
        Serial.print(dustDensity);
        break;
      }
     case 'I':
     {  
        Serial.print(hum);
        break;
     }
       case 'J':
     { 
        if(DHT11.temperature>=50)
      {  Serial.print("warn");
        analogWrite(PIN,255);}
        else
        Serial.print(tem);
        break;
     }
     delay(500);
   
   }
    if(c=='A')//向前
        {
         digitalWrite(IN1,HIGH);  
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,255); 
         analogWrite(ENB,255);
         }
      if(c=='B')//向后
        {
         digitalWrite(IN1,LOW);  
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,255); 
         analogWrite(ENB,255);
         }
      if(c=='C')//stop
        {
         digitalWrite(IN1,LOW);  
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,0); 
         analogWrite(ENB,0);
         }
      if(c=='D')
        {
         digitalWrite(IN1,HIGH);  
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,255); 
         analogWrite(ENB,100);
         }
      if(c=='E')
        {
         digitalWrite(IN1,HIGH);  
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,50); 
         analogWrite(ENB,255);
         }
      if(c=='F')
        {
         digitalWrite(IN1,LOW);  
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,LOW);
         analogWrite(ENA,255); 
         analogWrite(ENB,255);
         }
      if(c=='G')
        {
         digitalWrite(IN1,LOW);  
         digitalWrite(IN2,LOW);
         digitalWrite(IN3,LOW);
         digitalWrite(IN4,HIGH);
         analogWrite(ENA,255); 
         analogWrite(ENB,255);
         }
         }
}

 


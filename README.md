#include "SoftwareSerial.h"         
#include "DFRobotDFPlayerMini.h" 
#include <LedControl.h>
LedControl max7219_1=LedControl(6,4,5,1);                 //DIN---6,CLK---4,CS---5,numDevices=1
byte happy[8]={0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
byte sad[8]=  {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};	

SoftwareSerial mySoftwareSerial(11, 10);  
DFRobotDFPlayerMini myDFPlayer;   

int humi_sensor = A0;
int humi_value = 0;
int humi_threshold = 800;

int TrigPin = 3; 
int EchoPin = 2; 
float distance; 
int distance_threshold = 50; 
int int_distance;  

void setup() 
{
  delay(1000);
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  mySoftwareSerial.begin(9600);           //初始化软串口
  myDFPlayer.begin(mySoftwareSerial);     //初始化DFPlayerMini
  myDFPlayer.volume(15);                  //设置音量，范围0~30

  max7219_1.shutdown(0,false);
	max7219_1.setIntensity(0,3); 
	max7219_1.clearDisplay(0); 
}

void loop() 
{
  humi_value = get_humidity();
  int_distance = get_distance();
  delay(100);

  if (int_distance < distance_threshold)
  {
    Serial.println("detected!!!!!!!!");
    Serial.print("Humidity: ");
    Serial.print(humi_value);
    Serial.print(" || Distance: ");
    Serial.println(int_distance);
    delay(500);

    if (humi_value < humi_threshold)
    {
      display(happy);
      myDFPlayer.play(1);  
      delay(5000);
    }
    else
    {
      display(sad);
      myDFPlayer.play(2);  
      delay(5000);
    }

    while (int_distance < distance_threshold)
    {
      int_distance = get_distance();
      delay(100);
    }
    max7219_1.clearDisplay(0);
  }
}

int get_humidity()
{
  humi_value = analogRead(humi_sensor);
  Serial.print("Humidity: ");
  Serial.println(humi_value);
  return humi_value;
}

int get_distance()
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  distance = pulseIn(EchoPin, HIGH) / 58.0;
  int_distance = (int)distance;
  return int_distance;
}

void display(byte icon[]) 
{
	for(int i = 0; i < 8; i++)
	{
		max7219_1.setRow(0, i, icon[i]);
	}
}

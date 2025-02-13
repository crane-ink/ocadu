//DIGF-2002-501
//ocadu
//Aizixuan FU

#include <Keyboard.h>

int touchPin = A0;  
int buzzer = 8;    
int led = 13;        
int threshold = 200; 

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  Keyboard.begin();  
}

void loop() {
  int sensorValue = analogRead(touchPin);  
  Serial.println(sensorValue); 

  if (sensorValue == 0) {  
    digitalWrite(led, HIGH);
    tone(buzzer, 1000);  
    Serial.println("mouse_detected");

    Keyboard.press(KEY_RETURN); 
    delay(100); 
    Keyboard.releaseAll(); 
    delay(1000); 

    
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(500);
    Keyboard.releaseAll();

    delay(1000);  

    // 打开图片
    Keyboard.print("D:\\Desktop\\mouse.jpg");  
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.releaseAll();  

    delay(1000);  
  } else {
    digitalWrite(led, LOW);
    noTone(buzzer);  
  }

  delay(50);
}

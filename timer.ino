#include <Arduino.h>
#include <Wire.h>
#include<Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PIN_CDS 26
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int led = 20;
const int sw1 = 3;
const int sw2 = 4;
const int sw3 = 5;

int i =0;
int j = 0;
int a=0;
int b=0;

bool current_sw = HIGH;
bool last_sw = HIGH;

void setup() {
  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)){
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  }
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello, world!");
  display.display();
  delay(2000);

  pinMode(led,OUTPUT);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(sw3,INPUT);
  pinMode(PIN_CDS, INPUT);
  
}

void loop() {
    bool setting = 0;
    bool morning = 0;
    bool timeout = 0;
    
    int CDS_sensor =analogRead(26);
    
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(16, 24);
    display.print("count: ");
    display.println(j);
    display.display();
    
    if (CDS_sensor > 600){
      Serial.println("Good morning!");
      morning = true;
    }
    current_sw = digitalRead(sw1);
    
    if ((last_sw== LOW) && (current_sw ==HIGH)) {
      j = j+1;
    }
    last_sw = current_sw;
   
    Serial.print("j= ");
    Serial.println(j);
    while (morning ==true){
      i=i+1;
      display.clearDisplay();
      display.setTextSize(5);
      display.setTextColor(WHITE);
      display.setCursor(50, 16);
      display.println(i);
      display.display();
      delay(1000);
      if (i==j) {
        while (digitalRead(sw2) == HIGH) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(16, 16);
        display.println("Good morning!");
        display.display();
        
        digitalWrite(led,HIGH);
        delay(1000);
        digitalWrite(led,LOW);
        delay(1000);
        
        }
        i=0;
        j=0;
        a=0;
        b=0;
        timeout= true;
        break;
    }
    }
}
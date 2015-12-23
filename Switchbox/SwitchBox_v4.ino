/***************************************************   

  v4.0
  
  Controls the Switchbox

  Designed, Created, and Programmed by MARTECH Enterprises

  Open Source code written by Franklin Marquette for MARTECH Enterprises.  
  BSD license, all text above must be included in any redistribution
  
 ****************************************************//***************************************************/   

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

#define RELAY_ON 0
#define RELAY_OFF 1

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define RELAY_ON 1
#define RELAY_OFF 0

//buzzer pin
int buzzerPin = 2;
//led output
int LED_OUT = 3;
//indicator LED for bench LEDs
//int LED_IND = 4;
//output that turns everything off
int OFF = 5;
//on indicator
int STATUSLED_RELAY = 6;
//main control relay
int MAIN_RELAY = 7;

//turns LED on
int LED_ACTIVATOR = 14;
//led pot control
int LED_POTPIN = 15;
//activated when door opens from inside
int offind = 16;
//is key inserted?
int keyin = 17;

//default pot control value
int knobValue = 0;
//main control state
//int mainstate = 0;

void setup(){
  
  Serial.begin(9600);
  
  pinMode(LED_OUT, OUTPUT);
  pinMode(STATUSLED_RELAY, OUTPUT);
  pinMode(MAIN_RELAY, OUTPUT);
  pinMode(OFF, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  digitalWrite(OFF, LOW);
  
    BOOT_UP();
}

void loop() {
    /*int offread = analogRead(offind);
    int offfinal = offread/204.6; 
     
     if(offfinal > 3) {
       mainstate = 1;
     }*/
     
     LED_CONTROL();
     
     blah();
     
     key1();
     //OFf();
     }

void BOOT_UP() {
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
     display.begin(SSD1306_SWITCHCAPVCC);
     // init done
  
     //get display ready and display "logo"
     display.display();
     display.clearDisplay();
  
     display.setTextSize(3);
     display.setTextColor(BLACK, WHITE);
     display.setCursor(0, 20);
     display.println("MARTECH");
     display.display();
     delay(1899);
     display.clearDisplay();
  
     //do some fancy initializing shit
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System.");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_OFF);
     delay(1000);
  
     display.clearDisplay();
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System..");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_ON);
     delay(1000);
     digitalWrite(STATUSLED_RELAY, RELAY_OFF);
     delay(1000);
  
     display.clearDisplay();
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System...");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_ON);
     delay(1000);
     digitalWrite(STATUSLED_RELAY, RELAY_OFF);
     delay(1000);
  
     display.clearDisplay();
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System.");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_ON);
     delay(1000);
     digitalWrite(STATUSLED_RELAY, RELAY_OFF);
     delay(1000);
  
     display.clearDisplay();
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System..");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_ON);
     delay(1000);
     digitalWrite(STATUSLED_RELAY, RELAY_OFF);
     delay(1000);
  
     display.clearDisplay();
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System...");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_ON);
     delay(1000);
     digitalWrite(STATUSLED_RELAY, RELAY_OFF);
     delay(1000);
  
     display.clearDisplay();
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System.");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_ON);
     delay(1000);
     digitalWrite(STATUSLED_RELAY, RELAY_OFF);
     delay(1000);
  
     display.clearDisplay();
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System..");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_ON);
     delay(1000);
     digitalWrite(STATUSLED_RELAY, RELAY_OFF);
     delay(1000);
  
     display.clearDisplay();
     display.setTextSize(1.99);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     display.println("Initializing ");
     display.println("MARTECH");
     display.println("SWITCHBOX System...");
     display.display();
     digitalWrite(STATUSLED_RELAY, RELAY_ON);
     delay(1000);
     
  analogWrite(buzzerPin, 255);
  delay(100);
  analogWrite(buzzerPin, 0);
  delay(100);
  digitalWrite(MAIN_RELAY, HIGH);
  delay(1000);
  
     display.setTextSize(3);
     display.setTextColor(BLACK, WHITE);
     display.setCursor(0, 20);
     display.println("MARTECH");
     display.display();
  
}

void blah() {
  int offread = analogRead(offind);
  int offfinal = offread/204.6;
  
  if(offfinal > 4) {
    digitalWrite(MAIN_RELAY, LOW);
    digitalWrite(STATUSLED_RELAY, RELAY_OFF);
    digitalWrite(OFF, HIGH);
  }
  
    }
void key1(){
  int keyread = analogRead(keyin);
  int key = keyread/204.6;
  if(key > 4) {
      display.clearDisplay();
      display.setTextSize(2.59);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Key Inserted");
      tone(buzzerPin, 262, 500);
      delay(500);
      delay(1000);
      display.clearDisplay();
      display.setTextSize(1.99);
      display.println("Power save");
      display.println("over-ride activated");
      display.display();
      delay(2000);
      display.clearDisplay();
  }
}

/*void OFf() {
  
 int keyread = analogRead(keyin);
 int key = keyread/204.6;
 
  if (key < 3 && mainstate == 1) {
    display.clearDisplay();
    display.setTextSize(1.99);
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.println("      No       ");
    display.println("Activity");
    display.println("  Sensed  ");
    display.display();
    delay(2000);
    
    if(key > 3) {
                  
      mainstate = 0;
      
      display.clearDisplay();
      display.setTextSize(2.59);
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      display.println("Key Inserted");
      tone(buzzerPin, 262, 500);
      delay(500);
      delay(1000);
      display.clearDisplay();
      display.setTextSize(1.99);
      display.println("Power save");
      display.println("over-ride activated");
      display.display();
      delay(2000);
  }
    else if(key < 3 && mainstate == 1) {
      for(int i=0;i<8;i++){
      tone(buzzerPin, 262, 500);
      delay(1000);
      }
      if(key > 3) {
                  
        mainstate = 0;
        
        display.clearDisplay();
        display.setTextSize(2.59);
        display.setTextColor(WHITE);
        display.setCursor(0, 20);
        display.println("Key Inserted");
        tone(buzzerPin, 262, 500);
        delay(500);
        delay(1000);
        display.clearDisplay();
        display.setTextSize(1.99);
        display.println("Power save");
        display.println("over-ride activated");
        display.display();
        delay(2000);
  }
      else if(key < 3 && mainstate == 1) {
        delay(1000);
        if(key > 3) {
                  
          mainstate = 0;
          
          display.clearDisplay();
          display.setTextSize(2.59);
          display.setTextColor(WHITE);
          display.setCursor(0, 20);
          display.println("Key Inserted");
          tone(buzzerPin, 262, 500);
          delay(500);
          delay(1000);
          display.clearDisplay();
          display.setTextSize(1.99);
          display.println("Power save");
          display.println("over-ride activated");
          display.display();
          delay(2000);
  }
        else if(key < 3 && mainstate == 1) {
          delay(1000);
          if(key > 3) {
                  
            mainstate = 0;
            
            display.clearDisplay();
            display.setTextSize(2.59);
            display.setTextColor(WHITE);
            display.setCursor(0, 20);
            display.println("Key Inserted");
            tone(buzzerPin, 262, 500);
            delay(500);
            delay(1000);
            display.clearDisplay();
            display.setTextSize(1.99);
            display.println("Power save");
            display.println("over-ride activated");
            display.display();
            delay(2000);
  }
          else if(key < 3 && mainstate == 1) {
            delay(1000);
            if(key > 3) {
                  
               mainstate = 0;
              
               display.clearDisplay();
               display.setTextSize(2.59);
               display.setTextColor(WHITE);
               display.setCursor(0, 20);
               display.println("Key Inserted");
               tone(buzzerPin, 262, 500);
               delay(500);
               delay(1000);
               display.clearDisplay();
               display.setTextSize(1.99);
               display.println("Power save");
               display.println("over-ride activated");
               display.display();
               delay(2000);
  }
            else if (key < 3 && mainstate == 1) {
                display.clearDisplay();
                display.setTextSize(1.99);
                display.setTextColor(WHITE);
                display.setCursor(0, 20);
                display.println("System will ");
                display.println("shut down");
                display.println("in five seconds");
                display.display();
                delay(5000);
                
                if(key > 3) {
                  
                  mainstate = 0;
                  
                  display.clearDisplay();
                  display.setTextSize(2.59);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Key Inserted");
                  tone(buzzerPin, 262, 500);
                  delay(500);
                  delay(1000);
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.println("Power save");
                  display.println("over-ride activated");
                  display.display();
                  delay(2000);
  }
                else if(key < 3 && mainstate  == 1) {
                  
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System.");
                  display.display();

  
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System..");
                  display.display();
  
  
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System...");
                  display.display();
     
  
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System.");
                  display.display();
     
  
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System..");
                  display.display();
   
  
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System...");
                  display.display();
     
  
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System.");
                  display.display();
    
  
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System..");
                  display.display();
  
                  display.clearDisplay();
                  display.setTextSize(1.99);
                  display.setTextColor(WHITE);
                  display.setCursor(0, 20);
                  display.println("Shutting down ");
                  display.println("MARTECH");
                  display.println("SWITCHBOX System...");
                  display.display();
     
                  display.clearDisplay();

                  digitalWrite(MAIN_RELAY, LOW);
                  digitalWrite(STATUSLED_RELAY, RELAY_OFF);
                  digitalWrite(OFF, HIGH);
                }
            }
          }
      }
    }
    }
}//end main else if
}end SCAN*/

 void LED_CONTROL() {
  int LED_READ = analogRead(LED_ACTIVATOR);
  int LED_FINAL = LED_READ/204.6;
  
  if (LED_FINAL > 4) {
    
     knobValue = analogRead(LED_POTPIN)/4;
        
     analogWrite(LED_OUT, knobValue);
     }
      
   else {
      analogWrite(LED_OUT, 0);
          }
 }

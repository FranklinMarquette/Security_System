/***************************************************   
  v1.0
  
  Code to control Fingerprint Scanner
  
  Designed, Created, and Programmed by MARTECH Enterprises

  Open Source code written by Franklin Marquette for MARTECH Enterprises.  
  BSD license, all text above must be included in any redistribution
  
 ****************************************************/

//imported libraries
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#define SGRN 4//green strip
#define LGRN 5//green LED's
#define SRED 6//red strip
#define LRED 7//red LED's
#define ACCE 8//accepted signal to PLC
#define buzzerPin 9//buzzer
#define RON//signal from LCD to turn on red LED's

//relay values
#define RELAY_ON 0
#define RELAY_OFF 1

//read values
int RONREAD1 = 0;
int RONREAD2 = 0;

int getFingerprintIDez();//main fingerprint function

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);
  Serial.println("fingertest");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");

  //outputs
  pinMode(ACCE, OUTPUT);
  pinMode(SGRN, OUTPUT);
  pinMode(LGRN, OUTPUT);
  pinMode(SRED, OUTPUT);
  pinMode(LRED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  //default states
  digitalWrite(ACCE, RELAY_OFF);
  digitalWrite(LGRN, LOW);
  digitalWrite(SGRN, RELAY_OFF);
  digitalWrite(LRED, LOW);
  digitalWrite(SRED, RELAY_OFF);
  
  noTone(buzzerPin);
  
}

void loop()                     // run over and over again
{
  READ();
  getFingerprintIDez();//constantly run main fingerprint function
  delay(50);//don't ned to run this at full speed.
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  if(finger.fingerID == 1 && finger.confidence > 50) {//if ID = 1 and confidence is over 50 accept finger

    Serial.println("Accepted");
    
    //send signal to PLC
    digitalWrite(ACCE, RELAY_ON);
    delay(100);
    digitalWrite(ACCE, RELAY_OFF);

    //beep
    tone(buzzerPin, 255);
    delay(150);
    noTone(buzzerPin);

    //blink green LED's
    digitalWrite(LGRN, HIGH);
    digitalWrite(SGRN, RELAY_ON);
    delay(150);
    digitalWrite(SGRN, RELAY_OFF);
    digitalWrite(LGRN, LOW);
    delay(150);
    
    digitalWrite(LGRN, HIGH);
    digitalWrite(SGRN, RELAY_ON);
    delay(150);
    digitalWrite(SGRN, RELAY_OFF);
    digitalWrite(LGRN, LOW);
    delay(150);
    
  }

  else if(RONREAD1 == RONREAD2 && RONREAD1 == 0) {

    //turn red LED's on until penalty runs and PWR shuts FP off
    digitalWrite(LRED, HIGH);
    digitalWrite(SRED, RELAY_ON);
    
  }

  return finger.fingerID; 
}

void READ() {//read inputs

  RONREAD1 = digitalRead(RON);
  delay(10);
  RONREAD2 = digitalRead(RON);
  
}


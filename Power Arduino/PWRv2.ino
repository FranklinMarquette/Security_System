/***************************************************   
  v1.0
  
  Controls all power and startup functions - including the input panel drawer
  
  Designed, Created, and Programmed by MARTECH Enterprises

  Open Source code written by Franklin Marquette for MARTECH Enterprises.  
  BSD license, all text above must be included in any redistribution
  
 ****************************************************/

#define RFID_IN 2//RFID

#define WGLW 3//white drawer glow lighting
#define RSTR 4//red LEDs used only when Pulse method is called

#define buzzerPin 5//buzzer

//pneumatics
#define SEXT 6//extend drawer
#define SRET 7//retract drawer
#define SUP 8//raise cube
#define SDWN 9//lower cube

#define PIR_IN 10//PIR sensor

#define LKPO 11//turn LCD + Keypad Arduinos on

#define MN 12//main power for everything but PLC

//PLC signals to retract drawer
#define doorUnlock 13
#define penalty 22

#define hallEffect1 23//says that drawer is extended
#define hallEffect2 24//says that drawer is retracted
#define hallEffect3 25//says that cube is up
#define hallEffect4 26//says that cube is down

#define PWEL 27//play MP3 welcome message("Welcome . . . please follow the onscreen security procedures")
#define NACT 28//play MP3 no activity warning("No activity sensed . . . please return to panel")
#define SDWN 29//play MP3 shutting down message("System is shutting down")
#define HEL 30//play MP3 hello again message("Hello again . . . please continue the onscreen security procedures")

#define FAN 31//heating line fans

//relay values
#define RELAY_ON 0
#define RELAY_OFF 1

//default read values
int RFIDREAD1 = 0;
int RFIDREAD2 = 0;

int PIRREAD1 = 0;
int PIRREAD2 = 0;

int doorUnlockRead1 = 0;
int doorUnlockRead2 = 0;

int SEXTREAD1 = 0;
int SEXTREAD2 = 0;

int SRETREAD1 = 0;
int SRETREAD2 = 0;

int SUPREAD1 = 0;
int SUPREAD2 = 0;

int SDWNREAD1 = 0;
int SDWNREAD2 = 0;

int penaltyRead1 = 0;
int penaltyRead2 = 0;

int state = 0;//flag for PULSE method

void setup() {

  //inputs
  pinMode(RFID_IN, INPUT);
  pinMode(PIR_IN, INPUT);
  pinMode(doorUnlock, INPUT);
  pinMode(penalty, INPUT);
  pinMode(hallEffect1, INPUT);
  pinMode(hallEffect2, INPUT);
  pinMode(hallEffect3, INPUT);
  pinMode(hallEffect4, INPUT);

  //outputs
  pinMode(MN, OUTPUT);
  pinMode(LKPO, OUTPUT);

  pinMode(SEXT, OUTPUT);
  pinMode(SRET, OUTPUT);
  pinMode(SUP, OUTPUT);
  pinMode(SDWN, OUTPUT);

  pinMode(WGLW, OUTPUT);
  pinMode(RSTR, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(PWEL, OUTPUT);
  pinMode(NACT, OUTPUT);
  pinMode(SDWN, OUTPUT);
  pinMode(HEL, OUTPUT);

  pinMode(FAN, OUTPUT);

  //default states
  digitalWrite(MN, RELAY_OFF);
  
  digitalWrite(SEXT, RELAY_OFF);
  digitalWrite(SRET, RELAY_OFF);
  digitalWrite(SUP, RELAY_OFF);
  digitalWrite(SDWN, RELAY_OFF);

  digitalWrite(WGLW, RELAY_OFF);
  digitalWrite(RSTR, RELAY_OFF);

  digitalWrite(buzzerPin, RELAY_OFF);
  digitalWrite(LKPO, RELAY_OFF);
  
  digitalWrite(PWEL, RELAY_OFF);
  digitalWrite(NACT, RELAY_OFF);
  digitalWrite(SDWN, RELAY_OFF);
  digitalWrite(HEL, RELAY_OFF);

  digitalWrite(FAN, RELAY_ON);

  Serial.begin(9600);//start serial
  
  }

void(* resetFunc) (void) = 0;//declare reset function @ address 0

void loop() {

  READ();//constantly scan for input state changes
  RFID();//constantly run main method
  
}

void RFID() {

  if(SEXTREAD1 == SEXTREAD2 && SEXTREAD1 == 0 && SRETREAD1 == SRETREAD2 && SRETREAD1 == 1) {

    PIR();//if solenoid is extended scan for humans
   
  }

  else {

    //do nothing
    
  }

  if(RFIDREAD1 == RFIDREAD2 && RFIDREAD1 == 0) {

    //if an RFID card is scanned extend drawer and startup system
    EXTEND();
    delay(150);
    STARTUP();

  }

  else {

    //do nothing

  }

  if(doorUnlockRead1 == doorUnlockRead2 && doorUnlockRead1 == 0 || penaltyRead1 == penaltyRead2 && penaltyRead1 == 0) {

    //if either PLC activates Penalty(security step is wrong) or the door is unlocked retract the panel
    RETRACT();
    
  }

  else {

    //do nothing
  
  }

}

void PIR() {//scan for humans

  if(PIRREAD1 == PIRREAD2 && PIRREAD1 == 1) {//if there is no human

    //play message
    digitalWrite(NACT, RELAY_ON);
    delay(75);
    digitalWrite(NACT, RELAY_OFF);
    
    PULSE();//beep in an annoying fashion

    if(state == 1) {

      return;//end whole method

      state = 0;
      
    }

    if(PIRREAD1 == PIRREAD2 && PIRREAD1 == 1) {//if there is still no human

      //retract drawer and go to sleep
      RETRACT();

    }

    else {

      //do nothing

    }

  }

  else {

    //do nothing

  }

}

void PULSE() {

   for(int i=0;i<11;i++) {//beep 10 times along with pulsing red LED's

    READ();//keep on reading
    
    tone(buzzerPin, 262);
    digitalWrite(RSTR, RELAY_ON);
    delay(300);
    digitalWrite(RSTR, RELAY_OFF);
    noTone(buzzerPin);

    if(PIRREAD1 == PIRREAD2 && PIRREAD1 == 0) {//each time scan again for human - of there is one play message and exit loop

      digitalWrite(HEL, RELAY_ON);
      delay(75);
      digitalWrite(HEL, RELAY_OFF);
      
      break;//end for

      state = 1;//set flag

    }

    else {

      //do nothing

    }

    delay(200);
    
  }

}

void STARTUP() {//beep and then turn on glow LED's, turn on LCD + Keypad Arduino, play message

  tone(buzzerPin, 255);
  delay(100);
  noTone(buzzerPin);

  delay(200);

  tone(buzzerPin, 255);
  delay(100);
  noTone(buzzerPin);

  delay(200);

  tone(buzzerPin, 255);
  
  delay(100);
  noTone(buzzerPin);

  delay(200);

  tone(buzzerPin, 140);
  delay(350);
  tone(buzzerPin, 255);
  delay(150);
  noTone(buzzerPin);

  digitalWrite(LKPO, RELAY_ON);

  digitalWrite(PWEL, RELAY_ON);
  delay(75);
  digitalWrite(PWEL, RELAY_OFF);

  }

  void RETRACT() {//retract drawer lock door shut everything off and reset

    //blink red
      digitalWrite(RSTR, RELAY_ON);
      delay(250);
      digitalWrite(RSTR, RELAY_OFF);
      delay(250);

      digitalWrite(RSTR, RELAY_ON);
      delay(250);
      digitalWrite(RSTR, RELAY_OFF);
      delay(250);

    //play message
      digitalWrite(SDWN, RELAY_ON);
      delay(75);
      digitalWrite(SDWN, RELAY_OFF);
      
      digitalWrite(SDWN, RELAY_ON);
      digitalWrite(SUP, RELAY_OFF);

      if( SUPREAD1 == SUPREAD2 && SUPREAD1 == 1 && SDWNREAD1 == SDWNREAD2 && SDWNREAD1 == 0) {//if cube is lowered retract drawer
      
      digitalWrite(SEXT, RELAY_OFF);
      digitalWrite(SRET, RELAY_ON);

    }

    delay(1000);


    digitalWrite(RSTR, RELAY_OFF);
    digitalWrite(WGLW, RELAY_OFF);

    digitalWrite(buzzerPin, RELAY_OFF);
    digitalWrite(LKPO, RELAY_OFF);
    digitalWrite(PWEL, RELAY_OFF);

    digitalWrite(MN, RELAY_OFF);

    resetFunc();//call reset function

  }

  void EXTEND() {//unlock door and extend drawer

    digitalWrite(FAN, RELAY_OFF);
    
    digitalWrite(MN, RELAY_ON);

    digitalWrite(WGLW, RELAY_ON);

    if(SUPREAD1 == SUPREAD2 && SUPREAD1 == 1 && SDWNREAD1 == SDWNREAD2 && SDWNREAD1 == 0){//if cube is down extend drawer
 
      digitalWrite(SEXT, RELAY_ON);
      digitalWrite(SRET, RELAY_OFF);

      if(SEXTREAD1 == SEXTREAD2 && SEXTREAD1 == 0 && SRETREAD1 == SRETREAD2 && SRETREAD1 == 1) {//if drawer is extended raise cube
      
      digitalWrite(SDWN, RELAY_OFF);
      digitalWrite(SUP, RELAY_ON);

    }

    }

 }

 //all read functions
 void READ() {

  SEXTREAD1 = digitalRead(hallEffect1);
  delay(10);
  SEXTREAD2 = digitalRead(hallEffect1);

  SRETREAD1 = digitalRead(hallEffect2);
  delay(10);
  SRETREAD2 = digitalRead(hallEffect2);

  SUPREAD1 = digitalRead(hallEffect3);
  delay(10);
  SUPREAD2 = digitalRead(hallEffect3);

  SDWNREAD1 = digitalRead(hallEffect4);
  delay(10);
  SDWNREAD2 = digitalRead(hallEffect4);

  PIRREAD1 = digitalRead(PIR_IN);
  delay(10);
  PIRREAD2 = digitalRead(PIR_IN);

  doorUnlockRead1 = digitalRead(doorUnlock);
  delay(10);
  doorUnlockRead2 = digitalRead(doorUnlock);

  penaltyRead1 = digitalRead(penalty);
  delay(10);
  penaltyRead2 = digitalRead(penalty);

  RFIDREAD1 = digitalRead(RFID_IN);
  delay(10);
  RFIDREAD2 = digitalRead(RFID_IN);
  
 }
 




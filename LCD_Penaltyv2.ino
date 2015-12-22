/***************************************************   
  v1.0
  
  Displays all Security stage states as outputed from PLC
  Also controls the punishment if a security stage fails

  Designed, Created, and Programmed by MARTECH Enterprises

  Open Source code written by Franklin Marquette for MARTECH Enterprises.  
  BSD license, all text above must be included in any redistribution
  
 ****************************************************/

//import libraries
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);//(RS, E, D4, D5, D6, D7)

//penalty outputs
#define ALHT 8
#define SIR 9
#define AIR 24

#define DENY 22//play MP3 message("Access denied . . . prepare to be penalized")
#define ACCE 23//play MP3 message("Access granted")

#define RET 13//tells PWR arduino to retract drawer and sleep

#define FP_ACCEPT 10//PLC signal that fingerprint was accepted
#define KP_DECLINE 11//PLC signal that passcode was declined
#define KP_ACCEPT 12//PLC signal that passcode was accepted

#define GRN 25//main green LED's around door frame

#define buzzerPin 26//buzzer

#define DLOCK 27//send signal to door unlock arduino to unlock door

#define FPON 28//turn on FP arduino

#define FPRO 29//tell FP arduino to turn on red LED's

//relay values
#define RELAY_ON 1
#define RELAY_OFF 0

//default read values
int FPDECLINE_READ1 = 0;
int FPDECLINE_READ2 = 0;

int FPACCEPT_READ1 = 0;
int FPACCEPT_READ2 = 0;

int KPDECLINE_READ1 = 0;
int KPDECLINE_READ2 = 0;

int KPACCEPT_READ1 = 0;
int KPACCEPT_READ2 = 0;

int state = 0;//flag for ending FP scan early

void setup() {

  Serial.begin(9600);//begin serial

  //inputs
  pinMode(FP_ACCEPT, INPUT);
  pinMode(KP_ACCEPT, INPUT);
  pinMode(KP_DECLINE, INPUT);

  //outputs
  pinMode(ALHT, OUTPUT);
  pinMode(SIR, OUTPUT);
  pinMode(AIR, OUTPUT);

  pinMode(DENY, OUTPUT);
  pinMode(ACCE, OUTPUT);
  pinMode(RET, OUTPUT);
  pinMode(GRN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(DLOCK, OUTPUT);
  pinMode(FPON, OUTPUT);
  pinMode(FPRO, OUTPUT);

  //default states
  digitalWrite(ALHT, RELAY_OFF);
  digitalWrite(SIR, RELAY_OFF);
  digitalWrite(AIR, RELAY_OFF);

  digitalWrite(ACCE, RELAY_OFF);
  digitalWrite(DENY, RELAY_OFF);
  digitalWrite(RET, RELAY_OFF);
  digitalWrite(GRN, RELAY_OFF);
  digitalWrite(DLOCK, RELAY_OFF);
  digitalWrite(FPON, RELAY_OFF);
  pinMode(FPRO,   RELAY_OFF);
  noTone(buzzerPin);
  
  lcd.begin(8, 2);//initialize LCD

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   :Welc");
  lcd.setCursor(0, 1);
  lcd.print("ome:   ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLEASE E");
  lcd.setCursor(0, 1);
  lcd.print("NTER PIN");

}

void loop() {

  READ();//constantly read inputs
  ACT();//constantly run main method
  
}

void READ() {//reads all inputs

  FPACCEPT_READ1 = digitalRead(FP_ACCEPT);
  delay(10);
  FPACCEPT_READ2 = digitalRead(FP_ACCEPT);

  KPDECLINE_READ1 = digitalRead(KP_DECLINE);
  delay(10);
  KPDECLINE_READ2 = digitalRead(KP_DECLINE);

  KPACCEPT_READ1 = digitalRead(KP_ACCEPT);
  delay(10);
  KPACCEPT_READ2 = digitalRead(KP_ACCEPT);
  
}

void ACT() {

  if(KPACCEPT_READ1 == KPACCEPT_READ2 && KPACCEPT_READ1 == HIGH) {//if code was accepted

    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("   ACCE");
    lcd.setCursor(0, 1);
    lcd.print("PTED");

    digitalWrite(FPON, HIGH);
    
    delay(1000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  PLACE ");
    lcd.setCursor(0, 1);
    lcd.print("FINGER  ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   ON SC");
    lcd.setCursor(0, 1);
    lcd.print("ANNER   ");
    
    delay(1500);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WITHIN 5");
    lcd.setCursor(0, 1);
    lcd.print(" SECONDS");
    delay(1000);
    
    READ();//read values
    PRINT();//scan for print accepted
    if(state == 1) {//if print was accepted exit method early
      state = 0;
      return;
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       0");
    lcd.setCursor(0, 1);
    lcd.print("5       ");
    delay(1000);
    
    READ();
    PRINT();
    if(state == 1) {
      state = 0;
      return;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       0");
    lcd.setCursor(0, 1);
    lcd.print("4       ");
    delay(1000);
    READ();
    PRINT();
    if(state == 1) {
      state = 0;
      return;
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       0");
    lcd.setCursor(0, 1);
    lcd.print("3       ");
    delay(1000);
    
    READ();
    PRINT();
    if(state == 1) {
      state = 0;
      return;
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       0");
    lcd.setCursor(0, 1);
    lcd.print("2       ");
    delay(1000);
    
    READ();
    PRINT();
    if(state == 1) {
      state = 0;
      return;
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       0");
    lcd.setCursor(0, 1);
    lcd.print("1       ");
    delay(1000);
    
    READ();
    PRINT();
    if(state == 1) {
      state = 0;
      return;
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("       0");
    lcd.setCursor(0, 1);
    lcd.print("0       ");
    delay(500);

    DECLINE();
    
  }

  else if(KPDECLINE_READ1 == KPDECLINE_READ2 && KPDECLINE_READ1 == HIGH) {//if code was declined

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    DECL");
    lcd.setCursor(0, 1);
    lcd.print("INED    ");

    delay(150);

    //play message
    digitalWrite(DENY, RELAY_ON);
    delay(100);
    digitalWrite(DENY, RELAY_OFF);

    //dish out penalty
    PENALTY();
    
  }

}

void PENALTY() {

  digitalWrite(ALHT, RELAY_ON);
  digitalWrite(SIR, RELAY_ON);
  delay(100);
  digitalWrite(AIR, RELAY_ON);

  delay(2000);
  
}

void PRINT() {

  if(FPACCEPT_READ1 == FPACCEPT_READ2 && FPACCEPT_READ1 == HIGH) {//if print was accepted

    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("   ACCE");
    lcd.setCursor(0, 1);
    lcd.print("PTED");
    
    delay(2000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ACCESS ");
    lcd.setCursor(0, 1);
    lcd.print("GRANTED ");

    //play message
    digitalWrite(ACCE, RELAY_ON);
    delay(100);
    digitalWrite(ACCE, RELAY_OFF);

    for(int i = 0; i < 3; i++) {//beep and blink green
      
      tone(buzzerPin, 150);
      digitalWrite(GRN, RELAY_ON);
      delay(150);
      digitalWrite(GRN, RELAY_OFF);
      noTone(buzzerPin);
      delay(150);

    }

    digitalWrite(GRN, RELAY_ON);

    //tell door unlock arduino to unlock door
    digitalWrite(DLOCK, RELAY_ON);
    delay(100);
    digitalWrite(DLOCK, RELAY_OFF);

    state = 1;

  }

}

void DECLINE() {

    digitalWrite(FPRO, RELAY_ON);
    delay(75);
    digitalWrite(FPRO, RELAY_OFF);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    DECL");
    lcd.setCursor(0, 1);
    lcd.print("INED    ");

    delay(150);

    //play message
    digitalWrite(DENY, RELAY_ON);
    delay(100);
    digitalWrite(DENY, RELAY_OFF);

    //tell PWR to retract the drawer then everything will shut off and reset
    digitalWrite(RET, RELAY_ON);
    delay(100);
    digitalWrite(RET, RELAY_OFF);

    //dish out penalty
    PENALTY();
  
}


/***************************************************   

  v1.0
  
  Controls the keypad

  Designed, Created, and Programmed by MARTECH Enterprises

  Open Source code written by Franklin Marquette for MARTECH Enterprises.  
  BSD license, all text above must be included in any redistribution
  
 ****************************************************/

//import libraries
#include <Password.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define LGRN 9//green LED's
#define SGRN 10//green strip
#define LRED 11//red LED's
#define SRED 12//red strip
#define buzzerPin 13//buzzer

#define ACCE 22//accepted signal to PLC
#define DENY 23//declined signal to PLC

//relay values
#define RELAY_ON 0
#define RELAY_OFF 1

Password password = Password("1234");  // password
int dlugosc = 4;                        // length of the password
 
LiquidCrystal lcd(24, 25, 26, 27, 28, 29);//(RS, E, D4, D5, D6, D7)

int ilosc;//number of clicks

const byte ROWS = 4; // rows
const byte COLS = 3; // cols
 
char keys[ROWS][COLS] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8};
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  
  Serial.begin(9600);//begin serial

  Serial.println("begin");
  
  keypad.addEventListener(keypadEvent);//add keypad

  //outputs
  pinMode(LGRN, OUTPUT);
  pinMode(SGRN, OUTPUT);
  pinMode(LRED, OUTPUT);
  pinMode(SRED, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(ACCE, OUTPUT);
  pinMode(DENY, OUTPUT);

  //default states
  digitalWrite(LGRN, LOW);
  digitalWrite(SGRN, RELAY_OFF);
  digitalWrite(LRED, LOW);
  digitalWrite(SRED, RELAY_OFF);

  noTone(buzzerPin);

  digitalWrite(ACCE, RELAY_OFF);
  digitalWrite(DENY, RELAY_OFF);

  lcd.begin(16, 1);//initialize LCD
  
  lcd.clear();
  lcd.print("   ENTER CODE   ");
  delay(1500);

}

void loop() {

  keypad.getKey();//run main method

}

 void keypadEvent(KeypadEvent eKey) {
  
  switch (keypad.getState()) {
    
    case PRESSED://if key is pressed beep
   
      for(int i = 1; i <= 1; i++ ) {

        tone(buzzerPin, 255);  
        delay(50);            
        noTone(buzzerPin);  
        delay(50);      
       }    
 
     Serial.print("Pressed: ");
     Serial.println(eKey);
 
     switch (eKey) {

       case '#':
       break;
 
       case '*':
       break;

       default:
       ilosc=ilosc+1;
       password.append(eKey);
   }

    //print statements
    if(ilosc == 1) {
    
      lcd.clear();
      lcd.print("*_");
    
    }
  
    if(ilosc == 2) {

      lcd.clear();
      lcd.print("**_");
    
    }
  
    if(ilosc == 3) {
  
      lcd.clear();
      lcd.print("***_");
    
    }
  
    if(ilosc == 4) {

      lcd.clear();
      lcd.print("****_");
    
    }
  
    if(ilosc == 5) {

      lcd.clear();
      lcd.print("*****_");
    
    }
  
    if(ilosc == 6) {

      lcd.clear();
      lcd.print("******_");
    
    }
  
    if(ilosc == 7) {

      lcd.clear();
      lcd.print("*******_");
    
    }
  
    if(ilosc == 8) {

      lcd.clear();
      lcd.print("********_");
    
    }

    if(ilosc == 9) {
  
      lcd.clear();
      lcd.print("*********_");
    
    }
 
    if(ilosc == 10) {

      lcd.clear();
      lcd.print("**********_");
    
    }

    if(ilosc == 11) {

      lcd.clear();
      lcd.print("***********_");
    
    }

    if(ilosc == 12) {
 
      lcd.clear();
      lcd.print("************_");
    
    }

    if(ilosc == 13) {

      lcd.clear();
      lcd.print("*************_");
    
    }

    if(ilosc == 14) {
  
      lcd.clear();
      lcd.print("**************_");
    
    }

    if(ilosc == 15) {

      lcd.clear();
      lcd.print("***************");

    }

    //if number of entered keys equals passwords length check password
    if(ilosc == dlugosc) {
  
      delay(250);
      checkPassword();
      ilosc = 0;
    
    }
  }
}
 
void checkPassword() {

  delay(250);

  if (password.evaluate()) {//if password is correct

    digitalWrite(SRED, RELAY_OFF);//make sure red strip is off

    for(int i = 1; i <= 2; i++ ) {//beep and blink
   
      tone(buzzerPin, 255);  
      digitalWrite(SGRN, RELAY_ON);
      digitalWrite(LGRN, HIGH);
      delay(100);   
      digitalWrite(LGRN, LOW);   
      digitalWrite(SGRN, RELAY_OFF);      
      noTone(buzzerPin);  
      delay(100);   
    
    }    
    
    ilosc = 0;//reset

    //send signal to PLC
    digitalWrite(ACCE, RELAY_ON);
    delay(100); 
    digitalWrite(ACCE, RELAY_OFF);

    //print message
    lcd.clear();
    lcd.print("    ACCEPTED    "); 
    Serial.println("accepted");
    delay(150);
   
   } 
  
   else {//if its not correct

     digitalWrite(SGRN, RELAY_OFF);//make sure green strip is off

     //reset
     ilosc = 0;  
     password.reset();

     //send message to PLC
     digitalWrite(DENY, RELAY_ON);
     delay(100);
     digitalWrite(DENY, RELAY_OFF);  

     //turn red strip on until penalty runs and PWR shuts keypad off
     digitalWrite(SRED, RELAY_ON);
     digitalWrite(LRED, HIGH);

     //print message
     lcd.clear();
     lcd.print("     DENIED     ");
     Serial.println("denied");
     delay(150);
    
  }
}


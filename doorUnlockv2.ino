/***************************************************   

  v1.0
  
  Controls all door unlocking and door opening functions

  Designed, Created, and Programmed by MARTECH Enterprises

  Open Source code written by Franklin Marquette for MARTECH Enterprises.  
  BSD license, all text above must be included in any redistribution
  
 ****************************************************/

#define SOL1 2//pnuematic solenoid 1
#define SOL2 3//pnuematic solenoid 2
#define RET 4//tells PWR to retract drawer
#define ULO 5//LCD tells us to unlock door
#define RFLO 6//RF tells us to unlock door
#define MAG 7//tells us that door is open or shut

//relay values
#define RELAY_ON 0
#define RELAY_OFF 1

//default read values
int unlockRead1 = 0;
int unlockRead2 = 0;

int RFunlockRead1 = 0;
int RFunlockRead2 = 0;

int MAGREAD1 = 0;
int MAGREAD2 = 0;

void setup() {

  //inputs
  pinMode(ULO, INPUT);
  pinMode(RFLO, INPUT);
  pinMode(MAG, INPUT)

  //outputs
  pinMode(SOL1, OUTPUT);
  pinMode(SOL2, OUTPUT);
  pinMode(RET, OUTPUT);

  //default states
  digitalWrite(SOL1, RELAY_OFF);
  digitalWrite(SOL2, RELAY_ON);
  digitalWrite(RET, RELAY_OFF);

}

void loop() {

  MAIN();//constantly run main method

}

void MAIN() {

  //read inputs
  unlockRead1 = digitalRead(ULO);
  delay(10);
  unlockRead2 = digitalRead(ULO);

  RFunlockRead1 = digitalRead(RFLO);
  delay(10);
  RFunlockRead2 = digitalRead(RFLO);

  MAGREAD1 = digitalRead(MAG);
  delay(10);
  MAGREAD2 = digitalRead(MAG);

  if(unlockRead1 == unlockRead2 && unlockRead1 == 1 || RFunlockRead1 == RFunlockRead2 && RFunlockRead1 == 1 && MAGREAD1 == MAGREAD2 && MAGREAD1 == 0) {//if LCD arduino or RF arduino says so and door is closed unlock door for 3 seconds then lock

    //send signal to PWR arduino
    digitalWrite(RET, RELAY_ON);
    delay(100);
    digitalWrite(RET, RELAY_OFF);
    
    digitalWrite(SOL1, RELAY_ON);
    digitalWrite(SOL2, RELAY_OFF);

    while(MAGREAD1 == MAGREAD2 && MAGREAD1 == 1) {

      //do nothing
      
    }

    digitalWrite(SOL1, RELAY_OFF);
    digitalWrite(SOl2, RELAY_ON);
    
  }

  else {

    //do nothing
    
  }
  
}


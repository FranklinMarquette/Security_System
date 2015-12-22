/***************************************************   
  v1.0
  
  Code that controls Remote Activation of door lock

  Designed, Created, and Programmed by MARTECH Enterprises

  Open Source code written by Franklin Marquette for MARTECH Enterprises.  
  BSD license, all text above must be included in any redistribution
  
 ****************************************************/

#define RF_IN 2//is the remote telling us to do something?
#define ULO 3//signal to unlock door
#define REC 4//turn reciever off or on

//relay values
#define RELAY_ON 0
#define RELAY_OFF 1

//default read values
int RFREAD1 = 0;
int RFREAD2 = 0;

void setup() {

  //inputs
  pinMode(RF_IN, INPUT);

  //outputs
  pinMode(ULO, OUTPUT);
  pinMode(REC, OUTPUT);

  //default states
  digitalWrite(ULO, RELAY_OFF);
  digitalWrite(REC, RELAY_ON);

}

void(* resetFunc) (void) = 0;//declare reset function @ address 0

void loop() {

  RF();//run main method constantly

}

void RF() {

  //read values
  RFREAD1 = digitalRead(RF_IN);
  delay(10);
  RFREAD2 = digitalRead(RF_IN);

  if(RFREAD1 == RFREAD2 && RFREAD1 == 0) {//if the remote says so

    digitalWrite(reciever, RELAY_OFF);//shut reciever off(to stop constant signal)
    
    delay(500);
    
    //send signal to door unlock arduino
    digitalWrite(ULO, RELAY_ON);
    delay(100);
    digitalWrite(ULO, RELAY_OFF);

    delay(2000);

    resetFunc();//call reset function
    
  }

  else {

    //do nothing
 
  }
  
}


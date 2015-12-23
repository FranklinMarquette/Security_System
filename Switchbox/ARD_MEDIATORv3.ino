/***************************************************   

  v3.0
  
  Controls the startup functions of the Switchbox

  Designed, Created, and Programmed by MARTECH Enterprises

  Open Source code written by Franklin Marquette for MARTECH Enterprises.  
  BSD license, all text above must be included in any redistribution
  
 ****************************************************//***************************************************/   

int onPin = 2;//sig from MAIN BOARD to turn on Switchbox
int offPin = 3;//sig from MAIN BOARD to turn off Switchbox

int keyPin = 5;//sig from Switchbox key switch to turn on power save mode

//default read values
int onRead1 = 0;
int onRead2 = 0;

int offRead1 = 0;
int offRead2 = 0;

int keyRead1 = 0;
int keyRead2 = 0;

int relayOn = 4;//turns switchbox on
int relayKey = 6;//tells Switchbox Arduino that key has been inserted

//ddefault state
int keyState = 1;

#define RELAY_ON 0
#define RELAY_OFF 1

void setup() {
  // put your setup code here, to run once:
  pinMode(onPin, INPUT);
  pinMode(offPin, INPUT);
  pinMode(keyPin, INPUT);
  
  pinMode(relayOn, OUTPUT);
  pinMode(relayKey, OUTPUT);
  
  digitalWrite(relayOn, LOW);
  digitalWrite(relayKey, RELAY_ON);
}

void loop() {
  onRead1 = digitalRead(onPin);
  delay(10);
  onRead2 = digitalRead(onPin);
  
  offRead1 = digitalRead(offPin);
  delay(10);
  offRead2 = digitalRead(offPin);
  
  keyRead1 = digitalRead(keyPin);
  delay(10);
  keyRead2 = digitalRead(keyPin);
  
  if(onRead1==onRead2 && onRead1==HIGH){//if person enters
    digitalWrite(relayOn, HIGH);//turn on switchbox
  }
  
  if(keyRead1==keyRead2 && keyRead1==LOW && keyState==1){//if key switch is open
    keyState = 2;//change state
  }
  
  if(offRead1==offRead2 && offRead1==HIGH){//if person exits
    if(keyRead1==keyRead2 && keyRead1==LOW){//if key switch is open
    digitalWrite(relayOn, LOW);//turn off switchbox
    }
  }
  
  if(keyRead1==keyRead2 && keyRead1==HIGH && keyState==2){//if keyswitch is closed
    digitalWrite(relayKey, RELAY_OFF);//tell switchbox arduino that key is inserted
    delay(500);
    digitalWrite(relayKey, RELAY_ON);
    
    keyState = 1;
  }
  
}

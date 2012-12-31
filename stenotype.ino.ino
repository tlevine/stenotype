//LED, in case I need it
const int ledPin =  13;

//Index for loops
int i;

//Number of keys on the keyboard
const int keycount=22;
const int keydictsize = keycount + 1;
const int wordChordLength=128;

//Stenograph letters, used for serial testing
const char keydict[keydictsize] = "STKPWHRAO*EUFRPBLGTSDZ";
const char keydict_return='\n';
const char keydict_space=' ';

//Pin numbers and states
const int pins[keycount]={47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 11, 10, 9, 8};
int pinStates[keycount];

int numKeyPressed=1;
const int numPin=16;

// Output mode
// HIGH -> like a stenograph tape
// LOW  -> English
const int rawOutputModePin=15;

//The current chord
char rawChord[keycount];
char wordChord[wordChordLength];
int chordEmpty=1;
int chordEmptyThisIteration;
int rightAfterCarriageReturn=1;

//Turn pin states to off
void flushPinStates(){
  for (i=0;i<keycount;i++){
    pinStates[i]=0;
    rawChord[i]=keydict_space;
    chordEmpty=1;
  }
}

//Read my binary dictionary format.
//(Put the function here. Maybe call it readdict.)

void setup() {
  Serial.begin(9600);
  //Set pin states to off
  flushPinStates();

  // Initialize pins
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);

  for (i=0;i<keycount;i++){
    pinMode(pins[i],INPUT);
    digitalWrite(pins[i] 
    , LOW); // turn on pullup resistors
  }
  pinMode(rawOutputModePin,INPUT);
  digitalWrite(rawOutputModePin, LOW); // turn on pullup resistors
}

void loop(){
  chordEmptyThisIteration=1;
  //Set pin state based on the current chord.
  //Only turn pins on; pins are turned off on carriage returns (above).
  for (i=0;i<keycount;i++){
    if (digitalRead(pins[i])==HIGH){
      pinStates[i]=1;
      chordEmpty=0;
      chordEmptyThisIteration=0;
    }
  }
  
  //If a carriage return is not being triggered,
  if (!chordEmpty && chordEmptyThisIteration) {
    digitalWrite(ledPin,LOW);
    if (!chordEmpty){
      rightAfterCarriageReturn=0;
    }

  }
  else {
    //Carriage return triggered
    digitalWrite(ledPin,HIGH);

    // Populate the chord
    for (i=0;i<keycount;i++){
      if (pinStates[i]){
        rawChord[i]=keydict[i];
      }
    }

    //Print the chord if there's anything in it.
    if (chordEmpty==0){
      for (i=0;i<keycount;i++){
        Serial.print(rawChord[i]);
      }
      Serial.print('\n');
      flushPinStates();
    }  /* End chord for */    
  } // End carriage return if/else
}


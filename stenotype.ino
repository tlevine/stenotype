// An index for loops
int i;

// How many different keys do we have?
const int keyCount = 11;

//Stenograph letters
// const char keydict[keyCount] = "STKPWHRAO*EUFRPBLGTSDZ";
const char keyDict[keyCount] = "FRPBLGTSDZ";

//Pin numbers and states
const int pins[keyCount]={33, 35, 37, 39, 41, 43, 45, 47, 49, 51};

// The previous chord that was printed
char previousChord[keyCount];
int equalsPreviousChord;

// The current chord
char currentChord[keyCount];

// The keys currently pressed
char currentKeysPressed[keyCount];

// The previous keys pressed 
char previousKeysPressed[keyCount];

// Array equality
int hasChanged;
int stillPressed;

void setup() {
  Serial.begin(9600);
  for (i=0;i<keyCount;i++){
    // Initialize pins
    pinMode(pins[i],INPUT);

    // Turn on pullup resistors
    digitalWrite(pins[i] , LOW);

    // Start an empty chord.
    currentChord[i] = 0;
    currentKeysPressed[i] = 0;
    previousKeysPressed[i] = 0;
  }
}

void loop(){
  for (i=0;i<keyCount;i++){
    if (digitalRead(pins[i]) == HIGH) {
      currentKeysPressed[i] = keyDict[i];
    } else {
      currentKeysPressed[i] = 0;
    }
  }

  // Have the keys changed since last iteration?
  hasChanged = 0;
  for (i=0;i<keyCount;i++){
    if (currentKeysPressed[i] != previousKeysPressed[i]) {
      hasChanged = 1;
    }
  }
    
  // Are they still being pressed?
  stillPressed = 0;
  for (i=0;i<keyCount;i++){
    if (currentKeysPressed[i] != 0) {
//      Serial.print(currentKeysPressed[i]);
      stillPressed = 1;
      break;
    }
  }

  if (!hasChanged) {
    // No change since last iteration
  } else if (!stillPressed){
    // All keys been released.

    // Make sure that this isn't an error; check that this is different from the previous line.
    equalsPreviousChord = 1;
    for (i=0;i<keyCount;i++){
      if (currentChord[i] != previousChord[i]) {
        equalsPreviousChord = 0;
        break;
      }
    }

    // Print
    if (!equalsPreviousChord) {
      for (i=0;i<keyCount;i++){
        Serial.print(currentChord[i]);
      }
      Serial.print('\n');
    }

    // Reset
    for (i=0;i<keyCount;i++){
      previousChord[i] = currentChord[i];
      currentChord[i] = 0;
    }
  } else {
    // Pressed keys have changed
    for (i=0;i<keyCount;i++){
      if (currentKeysPressed[i] != 0){
        currentChord[i] = currentKeysPressed[i];
      }
    }
  }
  
  // Regardless,
  for (i=0;i<keyCount;i++){
    previousKeysPressed[i] = currentKeysPressed[i];
  }
  delay(10);
}

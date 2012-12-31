//Index for loops
int i;

// Number of different keys
const int keyCount = 11;

//Stenograph letters
// const char keydict[keydictsize] = "STKPWHRAO*EUFRPBLGTSDZ";
const char keyDict[keyCount] = "FRPBLGTSDZ";

//Pin numbers and states
const int pins[keyCount]={33, 35, 37, 39, 41, 43, 45, 47, 49, 51};

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
    currentChord[i] = ' ';
    currentKeysPressed[i] = ' ';
    previousKeysPressed[i] = ' ';
  }
}

void loop(){
  for (i=0;i<keyCount;i++){
    if (digitalRead(pins[i]) == HIGH) {
      currentKeysPressed[i] = keyDict[i];
    } else {
      currentKeysPressed[i] = ' ';
    }
  }
  delay(300);

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
    if (currentKeysPressed[i] != ' ') {
      stillPressed = 1;
      break;
    }
  }

  if (hasChanged) {
    Serial.print('a');
    // No change since last iteration
  } else if (!stillPressed){
    Serial.print('b');
    // All keys been released.
    for (i=0;i<keyCount;i++){
      Serial.print(currentChord[i]);
      currentChord[i] = ' ';
    }
  } else {
    Serial.print('c');
    // Pressed keys have changed
    for (i=0;i<keyCount;i++){
      if (currentKeysPressed[i] != ' '){
        currentChord[i] = currentKeysPressed[i];
      }
    }
  }
  
  // Regardless,
  for (i=0;i<keyCount;i++){
    previousKeysPressed[i] = currentKeysPressed[i];
  }
}

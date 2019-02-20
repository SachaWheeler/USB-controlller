int keyPin = 7;  // Set a button to any pin
int previousKeyPosition = 1;
int currentKeyPosition;
int keyDelay = 50;

int switchPin = 8;  // Set a button to any pin
int previousSwitchPosition = 1;
int currentSwitchPosition;
int switchDelay = 50;

int buttonPin = 9;  // Set a button to any pin
int previousButtonPosition = 1;
int currentButtonPosition;
int buttonDelay = 500;

bool activated = false;
bool armed = false;
bool recording = false;

int ledOff = 6;
int ledOn = 5;
int ledBlink = 4;
int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 500;

void setup()
{
  pinMode(keyPin, INPUT);  // Set the button as an input
  digitalWrite(keyPin, HIGH);  // Pull the button HIGH
  
  pinMode(switchPin, INPUT);  // Set the button as an input
  digitalWrite(switchPin, HIGH);  // Pull the button HIGH
  
  pinMode(buttonPin, INPUT);  // Set the button as an input
  digitalWrite(buttonPin, HIGH);  // Pull the button HIGH

  pinMode(ledOff, OUTPUT);
  digitalWrite(ledOff, HIGH);

  pinMode(ledOn, OUTPUT);
  digitalWrite(ledOn, LOW);

  pinMode(ledBlink, OUTPUT);
  digitalWrite(ledBlink, LOW);

  Serial.begin(9600); 
}

void loop()
{
    currentKeyPosition = digitalRead(keyPin);
    if (currentKeyPosition != previousKeyPosition)  // if the key position is changed
    {
      if(currentKeyPosition == LOW){ // which is on
        digitalWrite(ledOn, HIGH);
        digitalWrite(ledOff, LOW);
        activated = true;
        Serial.write("Key on\n");
        delay(keyDelay);
      }else{
        digitalWrite(ledOn, LOW);
        digitalWrite(ledOff, HIGH);
        activated = false;
        armed = false;
        recording = false;
        delay(keyDelay);
      }
      previousKeyPosition = currentKeyPosition;
    }

    currentSwitchPosition = digitalRead(switchPin);
    if (currentSwitchPosition != previousSwitchPosition)  // if the button is pressed or depressed
    {
      if(currentSwitchPosition == LOW){ // which is on
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press('1');  // send a command to the computer via Keyboard HID
        Keyboard.releaseAll();
        Serial.write("Switch on\n");
        delay(switchDelay);
        armed = true;
      }else{
        delay(switchDelay);
        armed = false;
        recording = false;
      }
      previousSwitchPosition = currentSwitchPosition;
    }

  
  // https://www.arduino.cc/en/Reference/KeyboardModifiers
  if(activated && armed){
    currentButtonPosition = digitalRead(buttonPin);
    if (currentButtonPosition != previousButtonPosition)  // if the button is pressed or depressed
    {
      if(currentButtonPosition == LOW){ // which is on
        Keyboard.write('r');  // send a 'r' to the computer via Keyboard HID
        Serial.write("Recording\n");
        recording = true;
        delay(buttonDelay);
      }else{
        Keyboard.write('p');  // send a 'p' to the computer via Keyboard HID
        Serial.write("Paused\n");
        recording = false;
        delay(buttonDelay);
      }
      previousButtonPosition = currentButtonPosition;
    }
    if(recording){
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
  
        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        }else{
          ledState = LOW;
        }
        digitalWrite(ledBlink, ledState);
     }
    }else{
      digitalWrite(ledBlink, LOW);
    }
  }
}
/*
 I@rp
 */


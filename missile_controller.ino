int keyPin = 7;  // Set a button to any pin
int previousKeyPosition = 1;
int currentKeyPosition;

int switchPin = 8;  // Set a button to any pin
int previousSwitchPosition = 1;
int currentSwitchPosition;

int buttonPin = 9;  // Set a button to any pin
int previousButtonPosition = 1;
int currentButtonPosition;

bool activated = false;
bool armed = false;

void setup()
{
  pinMode(keyPin, INPUT);  // Set the button as an input
  digitalWrite(keyPin, HIGH);  // Pull the button HIGH
  
  pinMode(switchPin, INPUT);  // Set the button as an input
  digitalWrite(switchPin, HIGH);  // Pull the button HIGH
  
  pinMode(buttonPin, INPUT);  // Set the button as an input
  digitalWrite(buttonPin, HIGH);  // Pull the button HIGH

  Serial.begin(9600); 
}

void loop()
{
  currentKeyPosition = digitalRead(keyPin);
  if (currentKeyPosition != previousKeyPosition)  // if the key position is changed
  {
    if(currentKeyPosition == LOW){ // which is on
      Serial.print("activated\t");
      Serial.print(currentKeyPosition);
      Serial.print("\n");
      delay(10);
      activated = true;
    }else{
      Serial.print("deactivated\t");
      Serial.print(currentKeyPosition);
      Serial.print("\n");
      delay(10);
      activated = false;
    }
    previousKeyPosition = currentKeyPosition;
  }

  currentSwitchPosition = digitalRead(switchPin);
  if (currentSwitchPosition != previousSwitchPosition)  // if the button is pressed or depressed
  {
    if(currentSwitchPosition == LOW){ // which is on
      Serial.print("armed\t");
      Serial.print(currentSwitchPosition);
      Serial.print("\n");
      //Keyboard.write('z');  // send a 'z' to the computer via Keyboard HID
      delay(10);
      armed = true;
    }else{
      Serial.print("disarmed\t");
      Serial.print(currentSwitchPosition);
      Serial.print("\n");
      delay(10);
      armed = false;
    }
    previousSwitchPosition = currentSwitchPosition;
  }

  

  if(activated && armed){
    currentButtonPosition = digitalRead(buttonPin);
    if (currentButtonPosition != previousButtonPosition)  // if the button is pressed or depressed
    {
      if(currentButtonPosition == LOW){ // which is on
        Serial.print("record\t");
        Serial.print(currentButtonPosition);
        Serial.print("\n");
        //Keyboard.write('r');  // send a 'r' to the computer via Keyboard HID
        delay(10);
      }else{
        Serial.print("pause\t");
        Serial.print(currentButtonPosition);
        Serial.print("\n");
        //Keyboard.write('p');  // send a 'p' to the computer via Keyboard HID
        delay(10);
      }
      previousButtonPosition = currentButtonPosition;
    }
  }
}


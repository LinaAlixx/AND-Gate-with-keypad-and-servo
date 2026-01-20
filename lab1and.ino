#include <Servo.h>

#include <Keypad.h>


const int buzz = 10;
const int servo = 13;
const int inAND = 11;
const int outAND = 12;

Servo myServo;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(inAND, INPUT);
  pinMode(buzz, OUTPUT);
  myServo.attach(servo);
  myServo.write(0);
  Serial.begin(9600);
  
  Serial.print("\nWrite Password if you done write # \n NOTE: don't forget to open the switch\n");
}

void loop() {
  static String inputCode;
  char key = keypad.getKey();
  myServo.detach();
  
  if (key) {
    Serial.print("Key Pressed: ");
    Serial.println(key);
   // inputCode = key;
    if (key == '#') {
      checkAccess(inputCode);
      inputCode = "";
    } else {
      inputCode += key;
    }
  }
}

void checkAccess(String code) {

  if(code == "0000"){
    digitalWrite(inAND, HIGH);
      if(digitalRead(outAND)){
        myServo.attach(servo);
        myServo.write(180);
        digitalWrite(buzz, LOW);
        Serial.println("Access Granted: Servo Activated");
        delay(500);
        myServo.write(0);
      }else {
        digitalWrite(buzz, HIGH);
        Serial.println("Access Denied: Buzzer Activated\nThe switch is OFF");
        delay(1000);
        digitalWrite(buzz, LOW);
  }
    
  }else{
    digitalWrite(inAND, LOW);
    digitalWrite(buzz, HIGH);
    Serial.println("Access Denied: Buzzer Activated\n Wrong PassWord!");
    delay(2000);
    digitalWrite(buzz, LOW);
  }
  
}

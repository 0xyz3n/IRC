#include <DabbleESP32.h>
#include<ESP32Servo.h>

// Movement
const byte motorPin_fwd[] = {34 , 35 , 32 , 33};
const byte motorPin_bkwrd[] = {25 , 26 , 14 , 12};


// Arm 
const byte servoPin[] = {18 , 19 , 21 , 23};
Servo servo[4];
byte angle[] = {0 , 0 , 0 , 0};
byte servoSelected = 0;
const uint64_t servoDelay[] = {50 , 50 , 50 , 50};

// if true , in  movement mode
bool mode = false;

void setup() {
  for(int i = 0; i < 4; i++) {
    servo[0].attach(servoPin[0]);
    pinMode(motorPin_fwd[0], OUTPUT);
    pinMode(motorPin_bkwrd[0], OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("ESPController");       //set bluetooth name of your device
}

void loop() {
  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    Serial.println("Selected servo 1");
    if(mode) {

    } else {
      servoSelected = 0;
      blink(1);
    }
    
  }

  if (GamePad.isDownPressed()) {
    Serial.println("Selected servo 2");
    servoSelected = 1;
    blink(2);
  }

  if (GamePad.isLeftPressed()) {
    Serial.println("Selected servo 3");
    servoSelected = 2;
    blink(3);
  }

  if (GamePad.isRightPressed()) {
    Serial.println("Selected servo 4");
    servoSelected = 3;
    blink(4);
  }

  if (GamePad.isCrossPressed()) {
    move(false);
  }

  if (GamePad.isTrianglePressed()) {
    move(true);
  }

  if (GamePad.isSquarePressed()) {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed()) {
    Serial.print("Circle");
  }

  if (GamePad.isSelectPressed()) {
    Serial.println("Select");
  }
  Serial.print('\t');


}

void move(bool up) {

  if(angle[servoSelected] == 180 && up) {
      angle[servoSelected] = 0;
    } else if(angle[servoSelected] == 0 && (!up)) {
      angle[servoSelected] = 180;
  }
  if(up) {
    servo[servoSelected].write(++angle[servoSelected]);
    delay(servoDelay[servoSelected]);
  } else {
    servo[servoSelected].write(--angle[servoSelected]);
    delay(servoDelay[servoSelected]);
  }
}

void blink(int n) {
  for(int i = 1; i <= n; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(125);
    digitalWrite(LED_BUILTIN, LOW);
    delay(125);
  }
}


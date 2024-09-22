#include <DabbleESP32.h>
#include <ESP32Servo.h>

// Setting PWM properties
const uint16_t freq[] = {30000 , 30000} ;
const byte pwmChannel[] = {0 , 1};
const byte resolution = 8;
const byte dutyCycle = 200;

// Movement
const byte motorPin_fwd[] = {16 , 17};   // IN Pins
const byte motorPin_bkwrd[] = { 25, 26}; // IN  pins
const byte motorPin_speed[] = {14 , 12}; // ENA Pins for Speed
const uint8_t movementDelay = 250; // Determines a minimum delay upto which robot will move for a single input


// Arm
const byte servoPin[] = { 18, 19, 21, 23 };
Servo servo[4];
byte angle[] = { 0, 0, 0, 0 };
byte servoSelected = 0;
const uint16_t servoDelay[] = { 50, 50, 50, 50 };

// if true , in  movement mode
bool mode = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    servo[i].attach(servoPin[i]);

    pinMode(motorPin_fwd[i], OUTPUT);
    pinMode(motorPin_bkwrd[i], OUTPUT);
    pinMode(motorPin_speed[i], OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);


  ledcSetup(pwmChannel[0], freq[0], resolution);
  ledcSetup(pwmChannel[1], freq[1], resolution);

  ledcAttachPin(motorPin_speed[0], pwmChannel[0]);
  ledcAttachPin(motorPin_speed[1], pwmChannel[1]);

  Serial.begin(115200);           // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("ESPController");  //set bluetooth name of your device
}

void loop() {
  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    
    if (mode) {
      blink(10 , 25);
      processMovement(0);
      delay(movementDelay);
      processMovement(-1);
    } else {
      Serial.println("Selected servo 1");
      servoSelected = 0;
      blink(1 , 125);
    }
  }

  if (GamePad.isDownPressed()) {
    if (mode) {
      blink(10 , 25);
      processMovement(1);
      delay(movementDelay);
      processMovement(-1);
    } else {
    Serial.println("Selected servo 3");
    servoSelected = 2;
    blink(3 , 125);
    }
  }

  if (GamePad.isLeftPressed()) {
    if (mode) {
      blink(10 , 25);
      processMovement(2);
      delay(movementDelay);
      processMovement(-1);
    } else {
    Serial.println("Selected servo 4");
    servoSelected = 3;
    blink(4 , 125);
    }
  }

  if (GamePad.isRightPressed()) {
    if (mode) {
      blink(10 , 25);
      processMovement(3);
      delay(movementDelay);
      processMovement(-1);
    } else {
    Serial.println("Selected servo 2");
    servoSelected = 1;
    blink(2 , 125);
    }
  }

  if (GamePad.isCrossPressed()) {
    moveServo(false);
  }

  if (GamePad.isTrianglePressed()) {
    moveServo(true);
  }

  // if (GamePad.isSquarePressed()) {
  //   Serial.print("Square");
  // }

  // if (GamePad.isCirclePressed()) {
  //   Serial.print("Circle");
  // }

  if (GamePad.isSelectPressed()) {
    mode = !mode;
    blink(1 , 200);
    if(mode) {
      blink(10 , 25);
      Serial.println("Movement mode");
    } else {
      Serial.println("Robotic arm controlling mode");
    }
    
  }

  if(GamePad.isStartPressed()) {
    if(mode) {
    blink(10 , 25);
    processMovement(-1);
    }
  }
}

void moveServo(bool up) {

  if (angle[servoSelected] == 180 && up) {
    angle[servoSelected] = 0;
  } else if (angle[servoSelected] == 0 && (!up)) {
    angle[servoSelected] = 180;
  }
  if (up) {
    servo[servoSelected].write(++angle[servoSelected]);
    delay(servoDelay[servoSelected]);
  } else {
    servo[servoSelected].write(--angle[servoSelected]);
    delay(servoDelay[servoSelected]);
  }
  Serial.println("Angle of Servo " + String(servoSelected + 1) + " :" + String(angle[servoSelected]));
}

void blink(uint8_t n , uint16_t d) {
  for (uint8_t i = 1; i <= n; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(d);
    digitalWrite(LED_BUILTIN, LOW);
    delay(d);
  }
}

// Movement part

// @dirn : 0 -> front ; 1 -> back; 2 -> left; 3 -> right
void processMovement(byte dirn) {
  switch(dirn) {

    case 0 :  Serial.println("Move forward");
              moveMotor(0 , 1);
              moveMotor(1 , 1);
              changeSpeed(255, 255);
              break;

    case 1 :  Serial.println("Move backward");
              moveMotor(0 , -1);
              moveMotor(1 , -1);
              changeSpeed(255, 255);
              break;

    case 2 :  Serial.println("Move left");
              moveMotor(0 , 1);
              moveMotor(1 , 0);
              changeSpeed(255, 255);
              break;
              
    case 3 :  Serial.println("Move right");
              moveMotor(0 , 0);
              moveMotor(1 , 1);
              changeSpeed(255, 255);
              break;
              
    default : Serial.println("STOP");
              moveMotor(0, 0);
              moveMotor(1, 0);
              break;
  }
}


void moveMotor(byte motor , byte direction) {
  switch(direction) {
    case 1 :  digitalWrite(motorPin_fwd[motor], HIGH);
              digitalWrite(motorPin_bkwrd[motor], LOW);
              break;

    case 0 :  digitalWrite(motorPin_fwd[motor],LOW);
              digitalWrite(motorPin_bkwrd[motor], LOW);
              break;

    case -1 : digitalWrite(motorPin_fwd[motor], LOW);
              digitalWrite(motorPin_bkwrd[motor], HIGH);
              break;
    default : digitalWrite(motorPin_fwd[motor],LOW);
              digitalWrite(motorPin_bkwrd[motor], LOW);
              break;
  }
}

void changeSpeed(uint8_t speed1 , uint8_t speed2) {
  ledcWrite(motorPin_speed[0], speed1);
  ledcWrite(motorPin_speed[1], speed2);
}

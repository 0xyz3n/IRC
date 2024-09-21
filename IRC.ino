#include <DabbleESP32.h>
#include<ESP32Servo.h>


// Define the servo pins
const byte servoPin[] = {18 , 19 , 21 , 23};
Servo servo[4];
byte angle[] = {0 , 0 , 0 , 0};

byte servoSelected = 0;



void setup() {
  servo[0].attach(servoPin[0]);
  servo[1].attach(servoPin[1]);
  servo[2].attach(servoPin[2]);
  servo[3].attach(servoPin[3]);

  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("ESPController");       //set bluetooth name of your device
}

void loop() {
  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    Serial.println("Selected servo 1");
    servoSelected = 0;
    blink(1);
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
    delay(50);
  } else {
    servo[servoSelected].write(--angle[servoSelected]);
    delay(50);
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


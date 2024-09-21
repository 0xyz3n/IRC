#include <DabbleESP32.h>
#include<ESP32Servo.h>


// Define the servo pins
const byte servoPin[] = {18 , 19 , 21 , 23};

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int servoSelected = 1;

byte angle[] = {0 , 0 , 0 , 0};

void setup() {
  servo1.attach(servoPin[0]);
  servo2.attach(servoPin[1]);
  servo3.attach(servoPin[2]);
  servo4.attach(servoPin[3]);

  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("ESPController");       //set bluetooth name of your device
}

void loop() {
  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    Serial.println("Selected servo 1");
    servoSelected = 1;
    blink(1);
  }

  if (GamePad.isDownPressed()) {
    Serial.println("Selected servo 2");
    servoSelected = 2;
    blink(2);
  }

  if (GamePad.isLeftPressed()) {
    Serial.println("Selected servo 3");
    servoSelected = 3;
    blink(3);
  }

  if (GamePad.isRightPressed()) {
    Serial.println("Selected servo 4");
    servoSelected = 4;
    blink(4);
  }

  if (GamePad.isCrossPressed()) {
    move(false);
  }

  if (GamePad.isTrianglePressed()) {
    move(true);
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
  }

    if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  Serial.print('\t');


}

void move(bool up) {
  if(servoSelected == 1) {
    if(angle[0] == 180 && up) {
      angle[0] = 0;
    } else if(angle[0] == 0 && (!up)) {
      angle[0] = 180;
    }
    if(up) {
      servo1.write(++angle[0]);
      delay(50);
    } else {
      servo1.write(--angle[0]);
      delay(50);
    }
  }

  if(servoSelected == 2) {
    if(angle[1] == 180 && up) {
      angle[1] = 0;
    } else if(angle[1] == 0 && (!up)) {
      angle[1] = 180;
    }
    if(up) {
      servo2.write(++angle[1]);
      delay(50);
    } else {
      servo2.write(--angle[1]);
      delay(50);
    }
  }

  if(servoSelected == 3) {
    if(angle[2] == 180 && up) {
      angle[2] = 0;
    } else if(angle[2] == 0 && (!up)) {
      angle[2] = 180;
    }
    if(up) {
      servo3.write(++angle[2]);
      delay(50);
    } else {
      servo3.write(--angle[2]);
      delay(50);
    }
  }

  if(servoSelected == 4) {
    if(angle[3] == 180 && up) {
      angle[3] = 0;
    } else if(angle[3] == 0 && (!up)) {
      angle[3] = 180;
    }
    if(up) {
      servo4.write(++angle[3]);
      delay(50);
    } else {
      servo4.write(--angle[3]);
      delay(50);
    }
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


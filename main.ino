#include <VarSpeedServo.h>

VarSpeedServo head; 
VarSpeedServo arm;

int headMaxOpen = 90;
int armMaxOpen = 12;

int headMaxClosed = 170;
int armMaxClosed = 135;

int armPosition = arm.read();
int headPosition = head.read();

const byte ledpins[3] = {9, 10, 11};

void setup() {

    //Attach button
    pinMode(2, INPUT);

    //Attach RGB lamp
    pinMode(ledpins[0], OUTPUT);
    pinMode(ledpins[1], OUTPUT);
    pinMode(ledpins[2], OUTPUT);

    //Attach servos
    head.attach(5);
    arm.attach(6);

    //Set servos to closed position
    head.write(headMaxClosed, 70); 
    arm.write(armMaxClosed, 70); 

    //Delay before loop begins
    delay(2000);
}

bool first = true;

void loop() {
    if(digitalRead(2)) {
        if(first) {
            simpleSwitchOff(90, 90, 90, 90);
        } else {
            shakeAndClose();
        }
        first = !first;
    }
}

void shakeAndClose() {
    turnLightOn();
    shakeHead(70, 180, 10);
    headUp(headMaxOpen, 180);
    armUp(armMaxOpen, 100);
    turnLightOff();
    armDown(armMaxClosed, 100);
    headDown(headMaxClosed, 100);
}

void simpleSwitchOff(int headOpenSpeed, int armOpenSpeed, int armCloseSpeed, int headCloseSpeed) {
    turnLightOn();
    headUp(headMaxOpen, headOpenSpeed); 
    armUp(armMaxOpen, armOpenSpeed); 
    delay(100);
    turnLightOff();
    delay(500);
    armDown(armMaxClosed, armCloseSpeed); 
    headDown(headMaxClosed, headCloseSpeed); 
}



void shakeHead(int degrees, int speed, int timesToShake) {
    bool shouldGoUp = true;
    for(int i = 0; i <= timesToShake; i++) {
        if (shouldGoUp) {
            headUp(head.read() - degrees, speed);
        } else {
            headDown(head.read() + degrees, speed);
        }
        shouldGoUp = !shouldGoUp;
    }
}

void shakeArm(int degrees, int speed, int timesToShake) {
    bool shouldGoUp = true;
    for(int i = 0; i <= timesToShake; i++) {
        if (shouldGoUp) {
            armUp(arm.read() - degrees, speed);
        } else {
            armDown(arm.read() + degrees, speed);
        }
        shouldGoUp = !shouldGoUp;
    }
}

void turnLightOff() {
    analogWrite(ledpins[0], 0);
    analogWrite(ledpins[1], 0);
    analogWrite(ledpins[2], 0);
}

void turnLightOn() {
    analogWrite(ledpins[0], 255);
    analogWrite(ledpins[1], 255);
    analogWrite(ledpins[2], 255);
}

void headUp(int degrees, int speed) {
    if(!(degrees > headMaxClosed || degrees < headMaxOpen)) {
        head.write(degrees, speed, true);
    }    
}

void headDown(int degrees, int speed) {
    if(!(degrees > headMaxClosed || degrees < headMaxOpen)) {
        head.write(degrees, speed, true);
    }
}

void armUp(int degrees, int speed) {
    if(!(degrees > armMaxClosed || degrees < armMaxOpen)) {
        arm.write(degrees, speed, true);
    }
}

void armDown(int degrees, int speed) {
    if(!(degrees > armMaxClosed || degrees < armMaxOpen)) {
        arm.write(degrees, speed, true);
    }        
}

#include <VarSpeedServo.h>
#include "utilfuncs.h"

VarSpeedServo head; 
VarSpeedServo arm;

Servo Head;
Servo Arm;

int headMaxOpen = 90;
int armMaxOpen = 12;

int headMaxClosed = 170;
int armMaxClosed = 135;

int armPosition = arm.read();
int headPosition = head.read();

typedef void (*sceneFunction)();

const int sceneCount = 2;
sceneFunction scenes[sceneCount] = { shakeAndClose, simpleSwitchOff };
int sceneIteration = 0;

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

    Head.servo = head;
    Head.MaxOpen = headMaxOpen;
    Head.MaxClosed = headMaxClosed;

    Arm.servo = arm;
    Arm.MaxOpen = armMaxOpen;
    Arm.MaxClosed = armMaxClosed;

    //Delay before loop begins
    delay(2000);
}

void loop() {
    if(digitalRead(2)) {
        head.attach(5);
        arm.attach(6);

        sceneFunction scene = scenes[sceneIteration];
        scene();
        sceneIteration++;
        if (sceneIteration >= sceneCount) {
            sceneIteration = 0;
        }

    } else {
        arm.detach();
        head.detach();
    }
}

void shakeAndClose() {
    turnLightOn();
    shake(Head, 70, 180, 10);
    move(Head, headMaxOpen, 180);
    move(Arm, armMaxOpen, 100);
    turnLightOff();
    move(Arm, armMaxClosed, 100);
    move(Head, headMaxClosed, 100);
} 

void simpleSwitchOff() {
    turnLightOn();
    move(Head, headMaxOpen, 150); 
    move(Arm, armMaxOpen, 150); 
    delay(100);
    turnLightOff();
    delay(500);
    move(Arm, armMaxClosed, 150); 
    move(Head, headMaxClosed, 150); 
}


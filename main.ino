#include <VarSpeedServo.h>
#include "utilfuncs.h"

VarSpeedServo head; 
VarSpeedServo arm;

Servo Head;
Servo Arm;

int headMaxOpen = 100;
int armMaxOpen = 12;

int headMaxClosed = 170;
int armMaxClosed = 140;

int minHeadOpenForArmOpen = 115;

int armPosition = arm.read();
int headPosition = head.read();

//For scenes:
typedef void (*sceneFunction)();

const int sceneCount = 10;
int sceneIteration = 0;

sceneFunction scenes[sceneCount] = { mediumSwitchOff, fastSwitchOffLowHead, slowOpenAndFastClose, lowShakeAndClose, blockAndShakeHead, fastSwitchOff, blockAndShakeArm, fastSwitchOffLowHead, closeAndHold, highShakeAndClose};


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
        delay(100);
        sceneIteration++;
        if (sceneIteration >= sceneCount) {
            sceneIteration = 0;
        }

    } else {
        arm.detach();
        head.detach();
    }
}

void slowSwitchOff() {
    turnLightOn();
    move(Head, headMaxOpen, 60); 
    move(Arm, armMaxOpen, 60); 
    delay(100);
    turnLightOff();
    delay(500);
    move(Arm, armMaxClosed, 60); 
    move(Head, headMaxClosed, 60); 
}

void mediumSwitchOff() {
    turnLightOn();
    move(Head, minHeadOpenForArmOpen, 100); 
    move(Arm, armMaxOpen, 100); 
    delay(100);
    turnLightOff();
    move(Arm, armMaxClosed, 100); 
    move(Head, headMaxClosed, 100); 
}

void fastSwitchOff() {
    turnLightOn();
    move(Head, headMaxOpen, 150); 
    move(Arm, armMaxOpen, 150); 
    delay(100);
    turnLightOff();
    move(Arm, armMaxClosed, 150); 
    move(Head, headMaxClosed, 150); 
}

void fastSwitchOffLowHead() {
    turnLightOn();
    move(Head, minHeadOpenForArmOpen, 150); 
    move(Arm, armMaxOpen, 150); 
    delay(100);
    turnLightOff();
    move(Arm, armMaxClosed, 150); 
    move(Head, headMaxClosed, 150); 
}

void highShakeAndClose() {
    turnLightOn();
    shake(Head, 70, 180, 8);
    move(Head, headMaxOpen, 180);
    move(Arm, armMaxOpen, 100);
    turnLightOff();
    move(Arm, armMaxClosed, 100);
    move(Head, headMaxClosed, 100);
    delay(500);
    warningOpen(Head, Arm, 60, 100, 2000);
} 

void closeAndHold() {
    turnLightOn();
    move(Head, headMaxOpen, 150); 
    move(Arm, armMaxOpen, 150); 
    delay(100);
    turnLightOff();
    move(Head, headMaxClosed - 40, 100); 
    delay(3000);
    move(Head, headMaxOpen, 150); 
    move(Arm, armMaxClosed, 150); 
    move(Head, headMaxClosed, 150); 
}

void lowShakeAndClose() {
    turnLightOn();
    shake(Head, 40, 200, 10);
    move(Head, headMaxOpen, 180);
    move(Arm, armMaxOpen, 100);
    turnLightOff();
    move(Arm, armMaxClosed, 100);
    move(Head, headMaxClosed, 100);
    delay(1000);
} 

void blockAndShakeArm() {
    turnLightOn();
    move(Head, minHeadOpenForArmOpen, 180);
    move(Arm, armMaxOpen, 100);
    turnLightOff();
    delay(1000);
    shake(Arm, 40, 180, 9, false);
    delay(500);
    move(Arm, armMaxClosed, 100);
    move(Head, headMaxClosed, 100);
} 

void blockAndShakeHead() {
    turnLightOn();
    move(Head, headMaxOpen, 180);
    move(Arm, armMaxOpen, 100);
    turnLightOff();
    delay(1000);
    shake(Head, 30, 180, 9, false);
    delay(500);
    move(Arm, armMaxClosed, 100);
    move(Head, headMaxClosed, 100);
}

void slowOpenAndFastClose() {
    turnLightOn();
    move(Head, headMaxOpen, 30);
    move(Arm, armMaxOpen, 180);
    turnLightOff();
    delay(200);
    move(Arm, armMaxClosed, 100);
    move(Head, headMaxClosed, 100);
} 



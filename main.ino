#include <VarSpeedServo.h>

VarSpeedServo head;
VarSpeedServo arm;

int headMaxOpen = 90;
int armMaxOpen = 15;

int headMaxClosed = 170;
int armMaxClosed = 135;

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

void loop() {
    
    if(digitalRead(2)) {
        turnLightOn();
        head.write(headMaxOpen, 180, true); 
        arm.write(armMaxOpen, 180, true); 
        delay(100);
        turnLightOff();
        delay(500);
        arm.write(armMaxClosed, 160, true); 
        head.write(headMaxClosed, 160, true); 
    } else {
        turnLightOff();
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
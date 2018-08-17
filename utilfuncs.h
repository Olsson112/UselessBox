#ifndef UTILITY_FUNCS
#define UTILITY_FUNCS

#include <VarSpeedServo.h>

const byte ledpins[3] = {9, 10, 11};

struct Servo {
    VarSpeedServo servo;
    int MaxClosed;
    int MaxOpen;
};

void move(Servo servo, int degrees, int speed) {
    if(!(degrees > servo.MaxClosed || degrees < servo.MaxOpen)) {
        servo.servo.write(degrees, speed, true);
    }   
}

void shake(Servo servo, int degrees, int speed, int timesToShake, bool shouldGoUp) {
    for(int i = 0; i <= timesToShake; i++) {
        if (shouldGoUp) {
            move(servo, servo.servo.read() - degrees, speed);
        } else {
            move(servo, servo.servo.read() + degrees, speed);
        }
        shouldGoUp = !shouldGoUp;
    }
}

void shake(Servo servo, int degrees, int speed, int timesToShake) {
    shake(servo, degrees, speed, timesToShake, true);
}


void changeLight(int r, int g, int b) {
    analogWrite(ledpins[0], r);
    analogWrite(ledpins[1], g);
    analogWrite(ledpins[2], b);
}

void turnLightOff() {
    changeLight(0, 0, 0);
}

void turnLightOn() {
    changeLight(255, 255, 255);
}



#endif
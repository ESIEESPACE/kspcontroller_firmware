
#include "Input.h"
Input input(&Serial);


void setup() {
    Serial.begin(9600);

    //Commands declaration
    input.addInput(7, "STG");
    input.addInput(6, "SAS");
    input.addInput(5, "RCS");
    input.addInput(4, "ABT");

    input.addInput(A0, "THT");
    input.addInput(A1, "ROL");
}


void loop() {
    input.checkCommands();
    delay(10);
}


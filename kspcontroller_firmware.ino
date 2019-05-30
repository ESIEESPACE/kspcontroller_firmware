
#include "Input.h"
Input input;


void setup() {
    Serial.begin(9600);

    //Commands declaration
    input.addCommand(7, "STG");
    input.addCommand(6, "SAS");
    input.addCommand(5, "RCS");
    input.addCommand(4, "DRC");
    input.addCommand(3, "VUE");

    input.addCommand(A0, "THT");
    input.addCommand(A1, "ROL");
}


void loop() {
    input.checkCommands();
    delay(10);
}

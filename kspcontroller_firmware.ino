
#include "Input.h"
#include "CommandReader.cpp"
Input input(&Serial);
CommandReader reader(&Serial);

void setup() {
    Serial.begin(9600);

    //Commands declaration
    input.addInput(7, "STG");
    input.addInput(6, "SAS");
    input.addInput(5, "RCS");
    input.addInput(4, "DRC");
    input.addInput(3, "VUE");

    input.addInput(A0, "THT");
    input.addInput(A1, "ROL");
    reader.addOutput("WTF", test);
}


void loop() {
    input.checkCommands();
    reader.process();
    delay(10);
}

void test(int count, String* params){
    Serial.println("Callback");
}



#include "Input.h"
#include "CommandReader.cpp"
#include "MemoryFree.h"
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

    reader.addOutput("MEM", memory);
    reader.addOutput("FRC", force);
    reader.addOutput("TEST", test);
}


void loop() {
    input.process();
    reader.process();
}

void memory(int count, String* params){
    Serial.print(F("MEM;"));
    Serial.println(MemoryFree::freeMemory(), DEC);
}

void force(int count, String* params){
    input.process(true);
}

void test(int count, String* params){
    Serial.println(F("Callback"));
    for (int i = 0; i < count; ++i) {
        Serial.println(String(i) + ": " + params[i]);
    }
}

static void showMemoryFree() {
    Serial.print(F("Free ram = "));
    Serial.println(MemoryFree::freeMemory(), DEC);
}
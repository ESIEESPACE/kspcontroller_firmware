
#include "Input.h"
#include "CommandReader.cpp"
#include "MemoryFree.h"
#include "Screen.h"

Screen_Widget sw[] = {
        Screen_Widget("APOAPSIS", "60 000 000", "km"),
        Screen_Widget("PERIAPSIS", "30 000 000", "km"),
        Screen_Widget("SPEED", "20000", "m/s"),
        Screen_Widget("TARGET DISTANCE", "60 000 000", "km"),
};

Input input(&Serial);
CommandReader reader(&Serial);
Screen screen(10, sw);

void setup() {
    Serial.begin(9600);
    Serial.print("INT\n");


    //Commands declaration
    input.addInput(7, "STG");
    input.addInput(6, "SAS");
    input.addInput(5, "RCS");
    input.addInput(4, "DRC");
    input.addInput(3, "VUE");

    input.addInput(A0, "THT");
    input.addInput(A1, "ROL");

    //Memoru
    reader.addOutput("MEM", memory);
    //Force send
    reader.addOutput("FRC", force);
    //Test command
    reader.addOutput("TEST", test);

    //Speed
    reader.addOutput("SPD", speed);
    //Apoapsis
    reader.addOutput("APO", apoapsis);
    //Periapsis
    reader.addOutput("PER", periapsis);
    //Target distance
    reader.addOutput("TDIS", target_distance);
}


void loop() {
    input.process();
    reader.process();
    screen.showWidgets();
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

void speed(int count, String* params){
    if(count != 1) return;
    sw[2].data = params[0];
}

void apoapsis(int count, String* params){
    if(count != 1) return;
    sw[0].data = params[0];
}

void periapsis(int count, String* params){
    if(count != 1) return;
    sw[1].data = params[0];
}

void target_distance(int count, String* params){
    if(count != 1) return;
    sw[3].data = params[0];
}


static void showMemoryFree() {
    Serial.print(F("Free ram = "));
    Serial.println(MemoryFree::freeMemory(), DEC);
}



#include "Input.h"
#include "CommandReader.cpp"
#include "MemoryFree.h"
#include "U8glib/U8glib.h"

Input input(&Serial);
CommandReader reader(&Serial);

U8GLIB_ST7920_128X64_4X u8g(10);


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

    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr( 0, 15, "Interfacing");
    } while( u8g.nextPage() );
    delay(2000);
    clearLCD();
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

void clearLCD(){
    u8g.firstPage();
    do {
    } while( u8g.nextPage() );
}
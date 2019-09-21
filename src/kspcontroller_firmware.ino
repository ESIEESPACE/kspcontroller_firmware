
#include "Input.h"
#include "CommandReader.cpp"
#include "MemoryFree.h"
#include "Screen.h"
#include "BarGraph.h"
#include "Wire.h"

Screen_Widget sw[] = {
        Screen_Widget("APOAPSIS", "60 000 000", "km"),
        Screen_Widget("PERIAPSIS", "30 000 000", "km"),
        Screen_Widget("SPEED", "20000", "m/s"),
        Screen_Widget("TARGET DISTANCE", "60 000 000", "km"),
};

Input input(&Serial);
CommandReader reader(&Serial);
Screen screen(49, sw);

BarGraph* barGraph[5];


int encoder_A = 8;
int encoder_B = 9;
int encoder_Clk = 7;

int encoder_val;
int encoder_Pos = 0;
int encoder_PinALast = LOW;
int encoder_ClkLast = LOW;
int encoder_n = LOW;

void setup() {
    Serial.begin(115200);
    Serial.println(F("INT"));

    //Commands declaration

    input.addInput(3, "CUS0");
    input.addInput(4, "CUS1");
    input.addInput(5, "CUS2");
    input.addInput(6, "CUS3");
    input.addInput(7, "CUS4");
    input.addInput(8, "CUS5");
    input.addInput(9, "CUS6");
    input.addInput(10, "CUS7");
    input.addInput(11, "CUS8");
    input.addInput(12, "CUS9");
    input.addInput(14, "BRK");
    input.addInput(34, "PSE");
    input.addInput(35, "STG");
    input.addInput(36, "TSPD");
    input.addInput(37, "TSLW");
    input.addInput(38, "ABT");
    input.addInput(24, "LGT");
    input.addInput(22, "EQP");
    input.addInput(26, "PBK");
    input.addInput(28, "RCS");
    input.addInput(30, "SAS");

    input.addInput(A0, "THT");
    input.addInput(A2, "ROL", -1, 1);
    input.addInput(A1, "YAW", -1, 1);
    input.addInput(A3, "PIT", -1, 1);
    input.addInput(A4, "FOR", -1, 1);
    input.addInput(A5, "TUR", -1, 1);
    input.addInput(A6, "ELV", -1, 1);

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

    reader.addOutput("BAR", bargraph);

    reader.addOutput("ALT", alti);



    barGraph[0] = new BarGraph(0x70);
    barGraph[1] = new BarGraph(0x71);
    barGraph[2] = new BarGraph(0x72);
    barGraph[3] = new BarGraph(0x73);
    barGraph[5] = new BarGraph(0x74);

    pinMode(encoder_A, INPUT);
    pinMode(encoder_B, INPUT);
    pinMode(encoder_Clk, INPUT);

    delay(1000);
}


void loop() {
    input.process();
    reader.process();
    screen.showWidgets();
    encoder_check();
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


void bargraph(int count, String* params){
    if(count != 2) return;
    barGraph[params[0].toInt()]->setLevel(params[1].toInt(), 1);
    barGraph[params[0].toInt()]->writeDisplay();
}

void alti(int count, String* params){
    if(count != 1) return;
    Segments segments(40, 41, 42, 1);
    segments.shutdown(0, false);  //turns on display
    segments.setIntensity(0, 15); // 15 = brightest
    params[0].replace("\r", "");
    params[0].replace("\n", "");
    int length =  params[0].length();
    for (int i = 0; i < length; i++) {

        segments.setDigit(0, (length > 7 ? 7 : length - 1) - i, String(params[0].charAt(i)).toInt(), false);
    }
}

void encoder_check() {
    encoder_n = digitalRead(encoder_A);
    if ((encoder_PinALast == LOW) && (encoder_n == HIGH)) {
        if (digitalRead(encoder_B) == LOW) {
            encoder_Pos--;
        } else {
            encoder_Pos++;
        }
    }
    encoder_PinALast = encoder_n;

    int val_clk = digitalRead(encoder_Clk);
    if(val_clk != encoder_ClkLast and val_clk == HIGH) {
        int val = encoder_Pos / 2 % 10;
        Serial.println("SASM;" + String(val));
    }
    encoder_ClkLast = val_clk;
}

static void showMemoryFree() {
    Serial.print(F("Free ram = "));
    Serial.println(MemoryFree::freeMemory(), DEC);
}


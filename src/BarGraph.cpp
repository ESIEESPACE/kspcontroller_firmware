//
// Created by louis on 16/06/19.
//

#include "BarGraph.h"


BarGraph::BarGraph(uint8_t address) {
    i2c_addr = address;

    Wire.begin();

    Wire.beginTransmission(i2c_addr);
    Wire.write(0x21);  // turn on oscillator
    Wire.endTransmission();

    setBrightness(15); // max brightness
}

void BarGraph::setBar(uint8_t bar, uint8_t color) {
    uint16_t a, c;

    if (bar < 12)
        c = bar / 4;
    else
        c = (bar - 12) / 4;

    a = bar % 4;
    if (bar >= 12)
        a += 4;

    //Serial.print("Ano = "); Serial.print(a); Serial.print(" Cath = "); Serial.println(c);
    if (color == LED_RED) {
        // Turn on red LED.
        displaybuffer[c] |= _BV(a);
        // Turn off green LED.
        displaybuffer[c] &= ~_BV(a + 8);
    } else if (color == LED_YELLOW) {
        // Turn on red and green LED.
        displaybuffer[c] |= _BV(a) | _BV(a + 8);
    } else if (color == LED_OFF) {
        // Turn off red and green LED.
        displaybuffer[c] &= ~_BV(a) & ~_BV(a + 8);
    } else if (color == LED_GREEN) {
        // Turn on green LED.
        displaybuffer[c] |= _BV(a + 8);
        // Turn off red LED.
        displaybuffer[c] &= ~_BV(a);
    }
}

void BarGraph::writeDisplay() {
    Wire.beginTransmission(i2c_addr);
    Wire.write((uint8_t) 0x00); // start at address $00

    for (uint8_t i = 0; i < 8; i++) {
        Wire.write(displaybuffer[i] & 0xFF);
        Wire.write(displaybuffer[i] >> 8);
    }
    Wire.endTransmission();
}

void BarGraph::clear(void) {
    for (uint8_t i = 0; i < 8; i++) {
        displaybuffer[i] = 0;
    }
}

void BarGraph::setBrightness(uint8_t b) {
    if (b > 15) b = 15;
    Wire.beginTransmission(i2c_addr);
    Wire.write(0xE0 | b);
    Wire.endTransmission();
}

void BarGraph::setLevel(uint8_t b, uint8_t color){
    for(int i = 0; i<24; i++){
        setBar(i, i < b ? color : 0);
    }
}
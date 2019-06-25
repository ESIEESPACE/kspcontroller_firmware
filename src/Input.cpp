//
// Created by louis on 30/05/19.
//

#include "Input.h"

Input::Input(Stream *_stream){
    this->stream = _stream;
}

void Input::addInput(int pin, const char* commandName, int min, int max) {
    command[pin] = commandName;
    this->min[pin] = min;
    this->max[pin] = max;
}

void Input::removeInput(int pin) {
    command[pin] = "";
    pinMode(pin, OUTPUT);
}

void Input::process() {
    process(false);
}

void Input::process(bool force) {
    for(int pin = 0; pin < NUM_DIGITAL_PINS; pin++) {
        if(String(command[pin]) != "") {
            //Detect if pin is an analog input
            if(pin < A0) digitalCheck(pin, force);
            else analogCheck(pin, force);
        }
    }
}

void Input::digitalCheck(int pin, bool force){
    pinMode(pin, INPUT_PULLUP);
    asm volatile ("NOP");
    int value = digitalRead(pin);

    //State change detection
    if(value != last_value[pin] || force) this->stream->print(String(command[pin]) + ";" + String(last_value[pin]) + "\n");

    last_value[pin] = value;
}

void Input::analogCheck(int pin, bool force){
    int value = analogRead(pin);

    //Less than 30, it is considered as 0
    if(value < 30) value = 0;

    //threshold detection
    if(!(last_value[pin] - ANALOG_THRESHOLD < value && value < last_value[pin] + ANALOG_THRESHOLD) || force) {
        this->stream->println(max[pin] - min[pin]);
        double trans_val = ((double)(value * (max[pin] - min[pin])) / (double)1023) + (double)min[pin];

        this->stream->print(String(command[pin]) + ";");
        this->stream->print(trans_val, 2);
        this->stream->print("\n");
        last_value[pin] = value;
    }
}

//
// Created by louis on 30/05/19.
//

#include "Input.h"

Input::Input(Stream *_stream){
    this->stream = _stream;
}

void Input::addInput(int pin, String commandName) {
    enable[pin] = true;
    command[pin] = commandName;
}

void Input::checkCommands() {
    for(int pin = 0; pin < NUM_DIGITAL_PINS; pin++) {
        if(enable[pin]) {
            //Detect if pin is an analog input
            if(pin < A0) digitalCheck(pin);
            else analogCheck(pin);
        }
    }
}

void Input::digitalCheck(int pin){
    pinMode(pin, INPUT_PULLUP);
    asm volatile ("NOP");
    int value = digitalRead(pin);

    //State change detection
    if(value != last_value[pin]) this->stream->print(command[pin] + ";" + String(last_value[pin]) + "\n");

    last_value[pin] = value;
}

void Input::analogCheck(int pin){
    int value = analogRead(pin);

    //Less than 30, it is considered as 0
    if(value < 30) value = 0;

    //threshold detection
    if(!(last_value[pin] - ANALOG_THRESHOLD < value && value < last_value[pin] + ANALOG_THRESHOLD)) {
        this->stream->print(command[pin] + ";");
        this->stream->print((double)value/(double)1023, 7);
        this->stream->print("\n");
        last_value[pin] = value;
    }
}
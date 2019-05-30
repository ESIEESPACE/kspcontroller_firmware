//
// Created by louis on 30/05/19.
//

#include "Input.h"

Input::Input(){

}

void Input::addCommand(int pin, String commandName) {
    enable[pin] = true;
    command[pin] = commandName;
    if(pin < A0) {
        pinMode(pin, INPUT_PULLUP);
    }
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
    int value = digitalRead(pin);

    //State change detection
    if(value != last_value[pin]) Serial.print(command[pin] + ";" + String(last_value[pin]) + "\n");

    last_value[pin] = value;
}

void Input::analogCheck(int pin){
    int value = analogRead(pin);

    //Less than 30, it is considered as 0
    if(value < 30) value = 0;
    
    //threshold detection
    if(!(last_value[pin] - ANALOG_THRESHOLD < value && value < last_value[pin] + ANALOG_THRESHOLD)) {
        Serial.print(command[pin] + ";");
        Serial.print((double)value/(double)1023, 2);
        Serial.print("\n");
        last_value[pin] = value;
    }
}

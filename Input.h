//
// Created by louis on 30/05/19.
//

#ifndef KSPCONTROLLER_FIRMWARE_INPUT_H
#define KSPCONTROLLER_FIRMWARE_INPUT_H


#include <WString.h>
#include <pins_arduino.h>
#include <Arduino.h>

class Input {

public:
    Input(Stream *_stream);
    void addInput(int pin, const char* commandName);
    void removeInput(int pin);
    void process();

private:
    void digitalCheck(int pin);
    void analogCheck(int pin);

    int last_value[NUM_DIGITAL_PINS];
    const char* command[NUM_DIGITAL_PINS];
    const int ANALOG_THRESHOLD = 40;
    Stream *stream;
};


#endif //KSPCONTROLLER_FIRMWARE_INPUT_H

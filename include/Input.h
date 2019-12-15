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
    void addInput(int pin, const char* commandName, int min = 0, int max = 1);
    void removeInput(int pin);
    void process(bool force);
    void process();

private:
    void digitalCheck(int pin, bool force);
    void analogCheck(int pin, bool force);

    int last_value[NUM_DIGITAL_PINS];
    const char* command[NUM_DIGITAL_PINS];
    int min[NUM_DIGITAL_PINS];
    int max[NUM_DIGITAL_PINS];
    const int ANALOG_THRESHOLD = 40;
    Stream *stream;
};


#endif //KSPCONTROLLER_FIRMWARE_INPUT_H

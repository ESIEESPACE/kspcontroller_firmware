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
    Input();
    void addCommand(int pin, String commandName);
    void checkcommands();

private:
    void digitalCheck(int pin);
    void analogCheck(int pin);

    int last_value[NUM_DIGITAL_PINS];
    bool enable[NUM_DIGITAL_PINS];
    String command[NUM_DIGITAL_PINS];
    const int ANALOG_THRESHOLD = 102;

};


#endif //KSPCONTROLLER_FIRMWARE_INPUT_H
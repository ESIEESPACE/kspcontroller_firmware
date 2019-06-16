//
// Created by louis on 16/06/19.
//

#ifndef KSPCONTROLLER_FIRMWARE_BARGRAPH_H
#define KSPCONTROLLER_FIRMWARE_BARGRAPH_H

#include "Wire.h"
#define LED_ON 1
#define LED_OFF 0

#define LED_RED 1
#define LED_YELLOW 2
#define LED_GREEN 3


class BarGraph {
public:
    BarGraph(uint8_t address);
    void setBar(uint8_t bar, uint8_t color);
    void writeDisplay();
    void clear();
    void setBrightness(uint8_t b);

private:
    uint16_t displaybuffer[8];
    uint8_t i2c_addr;
};


#endif //KSPCONTROLLER_FIRMWARE_BARGRAPH_H

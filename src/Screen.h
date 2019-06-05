//
// Created by louis on 05/06/19.
//

#ifndef KSPCONTROLLER_FIRMWARE_SCREEN_H
#define KSPCONTROLLER_FIRMWARE_SCREEN_H

#include "U8glib/U8glib.h"

class Screen {
public:
    Screen(uint8_t cs);


private:
    void clearLCD();
    U8GLIB_ST7920_128X64_4X u8g;
};


#endif //KSPCONTROLLER_FIRMWARE_SCREEN_H

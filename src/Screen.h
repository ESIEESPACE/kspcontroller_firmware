//
// Created by louis on 05/06/19.
//

#ifndef KSPCONTROLLER_FIRMWARE_SCREEN_H
#define KSPCONTROLLER_FIRMWARE_SCREEN_H

#include "U8glib/U8glib.h"
#include "Arduino.h"

class Screen_Widget{
public:
    String title;
    String data;
    String unit;
    Screen_Widget(String title, String data, String unit);
    Screen_Widget(String title, String data);
};

class Screen {
public:
    Screen(uint8_t cs, Screen_Widget sw[]);
    void showWidgets();

private:
    void clearLCD();
    U8GLIB_ST7920_128X64_4X u8g;
    Screen_Widget *screenWidget;
};


#endif //KSPCONTROLLER_FIRMWARE_SCREEN_H

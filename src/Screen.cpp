//
// Created by louis on 05/06/19.
//

#include "Screen.h"

Screen_Widget::Screen_Widget(String title, String data, String unit) {
    this->title = title;
    this->data = data;
    this->unit = unit;
}

Screen_Widget::Screen_Widget(String title, String data) {
    Screen_Widget(title, data, "");
}

Screen::Screen(uint8_t cs, Screen_Widget sw[]) : u8g(cs) {
    screenWidget = sw;
    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_unifont);
        //u8g.setFont(u8g_font_osb21);
        u8g.drawStr(0, 22, "KSP");
        u8g.drawStr(0, 42, "Controller");
    } while (u8g.nextPage());
}

void Screen::clearLCD() {
    u8g.firstPage();
    do {
    } while (u8g.nextPage());
}

void Screen::showWidgets() {
    u8g.firstPage();

    do {
        u8g.drawHLine(0, 32, 128);
        u8g.drawVLine(63, 0, 64);

        u8g.setFont(u8g_font_5x8);

        for (int i = 0; i < 4; ++i) {
            int initX = 65 * (i%2) + 1;
            int initY = i < 2 ? 0 : 33;

            u8g.setFont(u8g_font_5x8);
            for (int j = 0; j < screenWidget[i].title.length()/12 + 1; ++j) {
                u8g.drawStr(initX, initY + 8 * (j+1), screenWidget[i].title.substring(j*12, (j+1)*12).c_str());
            }

            u8g.setFont(u8g_font_5x7);
            u8g.drawStr(initX, initY + 24, screenWidget[i].data.c_str());
            u8g.setFont(u8g_font_4x6);
            u8g.drawStr(initX, initY + 30, screenWidget[i].unit.c_str());
        }



    } while ( u8g.nextPage() );
}
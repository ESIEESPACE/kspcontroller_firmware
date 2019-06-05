//
// Created by louis on 05/06/19.
//

#include "Screen.h"

Screen::Screen(uint8_t cs) : u8g(cs) {
    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_unifont);
        //u8g.setFont(u8g_font_osb21);
        u8g.drawStr( 0, 22, "KSP");
        u8g.drawStr( 0, 42, "Controller");
    } while( u8g.nextPage() );
}

void Screen::clearLCD(){
    u8g.firstPage();
    do {
    } while( u8g.nextPage() );
}
//
// Created by louis on 16/06/19.
//

#ifndef KSPCONTROLLER_FIRMWARE_BARGRAPH_H
#define KSPCONTROLLER_FIRMWARE_BARGRAPH_H

#include "Wire.h"
#include "Arduino.h"
#define LED_ON 1
#define LED_OFF 0

#define LED_RED 1
#define LED_YELLOW 2
#define LED_GREEN 3
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

#define SEVENSEG_DIGITS 5


const static byte charTable[] PROGMEM  = {
        B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
        B01111111,B01111011,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,
        B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
        B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
        B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
        B00000000,B00000000,B00000000,B00000000,B10000000,B00000001,B10000000,B00000000,
        B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
        B01111111,B01111011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
        B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
        B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00000000,B00000000,
        B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
        B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000,
        B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
        B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00010101,B00011101,
        B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
        B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
};


class MAX7219 {
public:
    MAX7219(uint8_t address);
    void setBrightness(uint8_t b);
    void blinkRate(uint8_t b);
    void writeDisplay(void);
    void clear(void);

    uint16_t displaybuffer[8];

    void init(uint8_t a);
protected:
    uint8_t i2c_addr;
};


class BarGraph : public MAX7219 {
public:
    BarGraph(uint8_t address);
    void setBar(uint8_t bar, uint8_t color);
    void setLevel(uint8_t b, uint8_t color);
};


class Segments {

public:
    Segments(int dataPin, int clkPin, int csPin, int numDevices=1);
    int getDeviceCount();
    void shutdown(int addr, bool status);
    void setScanLimit(int addr, int limit);
    void setIntensity(int addr, int intensity);
    void clearDisplay(int addr);
    void setLed(int addr, int row, int col, boolean state);
    void setRow(int addr, int row, byte value);
    void setColumn(int addr, int col, byte value);
    void setDigit(int addr, int digit, byte value, boolean dp);
    void setChar(int addr, int digit, char value, boolean dp);

private:
    /* The array for shifting the data to the devices */
    byte spidata[16];
    /* Send out a single command to the device */
    void spiTransfer(int addr, byte opcode, byte data);

    /* We keep track of the led-status for all 8 devices in this array */
    byte status[64];
    /* Data is shifted out of this pin*/
    int SPI_MOSI;
    /* The clock is signaled on this pin */
    int SPI_CLK;
    /* This one is driven LOW for chip selectzion */
    int SPI_CS;
    /* The maximum number of devices we use */
    int maxDevices;
};




#endif //KSPCONTROLLER_FIRMWARE_BARGRAPH_H

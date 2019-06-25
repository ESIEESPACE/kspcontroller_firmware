//
// Created by louis on 16/06/19.
//

#include "BarGraph.h"

MAX7219::MAX7219(uint8_t address) {
    i2c_addr = address;


    Wire.begin();

    Wire.beginTransmission(i2c_addr);
    Wire.write(0x21);  // turn on oscillator
    Wire.endTransmission();

    setBrightness(15); // max brightness
}

void MAX7219::setBrightness(uint8_t b) {
    if (b > 15) b = 15;
    Wire.beginTransmission(i2c_addr);
    Wire.write(0xE0 | b);
    Wire.endTransmission();
}

void MAX7219::clear(void) {
    for (uint8_t i = 0; i < 8; i++) {
        displaybuffer[i] = 0;
    }
}

void MAX7219::writeDisplay() {
    Wire.beginTransmission(i2c_addr);
    Wire.write((uint8_t) 0x00); // start at address $00

    for (uint8_t i = 0; i < 8; i++) {
        Wire.write(displaybuffer[i] & 0xFF);
        Wire.write(displaybuffer[i] >> 8);
    }
    Wire.endTransmission();
}

BarGraph::BarGraph(uint8_t t) : MAX7219(t) {

}

void BarGraph::setBar(uint8_t bar, uint8_t color) {
    uint16_t a, c;

    if (bar < 12)
        c = bar / 4;
    else
        c = (bar - 12) / 4;

    a = bar % 4;
    if (bar >= 12)
        a += 4;

    //Serial.print("Ano = "); Serial.print(a); Serial.print(" Cath = "); Serial.println(c);
    if (color == LED_RED) {
        // Turn on red LED.
        displaybuffer[c] |= _BV(a);
        // Turn off green LED.
        displaybuffer[c] &= ~_BV(a + 8);
    } else if (color == LED_YELLOW) {
        // Turn on red and green LED.
        displaybuffer[c] |= _BV(a) | _BV(a + 8);
    } else if (color == LED_OFF) {
        // Turn off red and green LED.
        displaybuffer[c] &= ~_BV(a) & ~_BV(a + 8);
    } else if (color == LED_GREEN) {
        // Turn on green LED.
        displaybuffer[c] |= _BV(a + 8);
        // Turn off red LED.
        displaybuffer[c] &= ~_BV(a);
    }
}

void BarGraph::setLevel(uint8_t b, uint8_t color){
    for(int i = 0; i<24; i++){
        setBar(i, i < b ? color : 0);
    }
}

Segments::Segments(int dataPin, int clkPin, int csPin, int numDevices) {
    SPI_MOSI=dataPin;
    SPI_CLK=clkPin;
    SPI_CS=csPin;
    if(numDevices<=0 || numDevices>8 )
        numDevices=8;
    maxDevices=numDevices;
    pinMode(SPI_MOSI,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
    digitalWrite(SPI_CS,HIGH);
    SPI_MOSI=dataPin;
    for(int i=0;i<64;i++)
        status[i]=0x00;
    for(int i=0;i<maxDevices;i++) {
        spiTransfer(i,OP_DISPLAYTEST,0);
        //scanlimit is set to max on startup
        setScanLimit(i,7);
        //decode is done in source
        spiTransfer(i,OP_DECODEMODE,0);
        clearDisplay(i);
        //we go into shutdown-mode on startup
        shutdown(i,true);
    }
}

int Segments::getDeviceCount() {
    return maxDevices;
}

void Segments::shutdown(int addr, bool b) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(b)
        spiTransfer(addr, OP_SHUTDOWN,0);
    else
        spiTransfer(addr, OP_SHUTDOWN,1);
}

void Segments::setScanLimit(int addr, int limit) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(limit>=0 && limit<8)
        spiTransfer(addr, OP_SCANLIMIT,limit);
}

void Segments::setIntensity(int addr, int intensity) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(intensity>=0 && intensity<16)
        spiTransfer(addr, OP_INTENSITY,intensity);
}

void Segments::clearDisplay(int addr) {
    int offset;

    if(addr<0 || addr>=maxDevices)
        return;
    offset=addr*8;
    for(int i=0;i<8;i++) {
        status[offset+i]=0;
        spiTransfer(addr, i+1,status[offset+i]);
    }
}

void Segments::setLed(int addr, int row, int column, boolean state) {
    int offset;
    byte val=0x00;

    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7 || column<0 || column>7)
        return;
    offset=addr*8;
    val=B10000000 >> column;
    if(state)
        status[offset+row]=status[offset+row]|val;
    else {
        val=~val;
        status[offset+row]=status[offset+row]&val;
    }
    spiTransfer(addr, row+1,status[offset+row]);
}

void Segments::setRow(int addr, int row, byte value) {
    int offset;
    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7)
        return;
    offset=addr*8;
    status[offset+row]=value;
    spiTransfer(addr, row+1,status[offset+row]);
}

void Segments::setColumn(int addr, int col, byte value) {
    byte val;

    if(addr<0 || addr>=maxDevices)
        return;
    if(col<0 || col>7)
        return;
    for(int row=0;row<8;row++) {
        val=value >> (7-row);
        val=val & 0x01;
        setLed(addr,row,col,val);
    }
}

void Segments::setDigit(int addr, int digit, byte value, boolean dp) {
    int offset;
    byte v;

    if(addr<0 || addr>=maxDevices)
        return;
    if(digit<0 || digit>7 || value>15)
        return;
    offset=addr*8;
    v=pgm_read_byte_near(charTable + value);
    if(dp)
        v|=B10000000;
    status[offset+digit]=v;
    spiTransfer(addr, digit+1,v);
}

void Segments::setChar(int addr, int digit, char value, boolean dp) {
    int offset;
    byte index,v;

    if(addr<0 || addr>=maxDevices)
        return;
    if(digit<0 || digit>7)
        return;
    offset=addr*8;
    index=(byte)value;
    if(index >127) {
        //no defined beyond index 127, so we use the space char
        index=32;
    }
    v=pgm_read_byte_near(charTable + index);
    if(dp)
        v|=B10000000;
    status[offset+digit]=v;
    spiTransfer(addr, digit+1,v);
}

void Segments::spiTransfer(int addr, volatile byte opcode, volatile byte data) {
    //Create an array with the data to shift out
    int offset=addr*2;
    int maxbytes=maxDevices*2;

    for(int i=0;i<maxbytes;i++)
        spidata[i]=(byte)0;
    //put our device data into the array
    spidata[offset+1]=opcode;
    spidata[offset]=data;
    //enable the line
    digitalWrite(SPI_CS,LOW);
    //Now shift out the data
    for(int i=maxbytes;i>0;i--)
        shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,spidata[i-1]);
    //latch the data onto the display
    digitalWrite(SPI_CS,HIGH);
}
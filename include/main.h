//
// Created by louis on 15/12/2019.
//

#ifndef KSPCONTROLLER_FIRMWARE_MAIN_H
#define KSPCONTROLLER_FIRMWARE_MAIN_H

#include "Arduino.h"
#include "Input.h"
#include "CommandReader.cpp"
#include "MemoryFree.h"
#include "Screen.h"
#include "../lib/MAX7219/BarGraph.h"
#include "Wire.h"

void memory(int count, String* params);
void force(int count, String* params);

void test(int count, String* params);

void speed(int count, String* params);

void apoapsis(int count, String* params);


void periapsis(int count, String* params);

void target_distance(int count, String* params);

void bargraph(int count, String* params);

void alti(int count, String* params);

void encoder_check();
static void showMemoryFree();

#endif //KSPCONTROLLER_FIRMWARE_MAIN_H


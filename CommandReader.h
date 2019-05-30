//
// Created by louis on 30/05/19.
//

#ifndef KSPCONTROLLER_FIRMWARE_COMMANDREADER_H
#define KSPCONTROLLER_FIRMWARE_COMMANDREADER_H

#include <WString.h>
#include <Arduino.h>
#include "StringSplitter.h"

struct CommandReaderStruct {
    const char* command;
    void (*callback)(int, String*);
};

class CommandReader {
public:
    CommandReader(Stream *_stream);
    void addOutput(const char* command, void (*callback)(int, String*));
    void addOutput(String command, void (*callback)(int, String*));
    void addOutput(CommandReaderStruct commandReaderStruct);
    void process();

private:
    char buffer[50];
    int pointer = 0;
    Stream *stream;
    CommandReaderStruct commands[20];
    int commandCounter = 0;
};


#endif //KSPCONTROLLER_FIRMWARE_COMMANDREADER_H

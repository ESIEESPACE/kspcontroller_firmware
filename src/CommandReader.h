//
// Created by louis on 30/05/19.
//

#ifndef KSPCONTROLLER_FIRMWARE_COMMANDREADER_H
#define KSPCONTROLLER_FIRMWARE_COMMANDREADER_H

#include <WString.h>
#include <Arduino.h>
#include "MemoryFree.h"

#define MAX_OUTPUT 10

struct CommandReaderStruct {
    const char* command;
    void (*callback)(int, String*);

};

class CommandReader {
public:
    inline CommandReader(Stream *_stream);
    inline void addOutput(const char* command, void (*callback)(int, String*));
    inline void addOutput(String command, void (*callback)(int, String*));
    inline void addOutput(CommandReaderStruct commandReaderStruct);
    inline void process();

private:
    String buffer;
    Stream *stream;
    CommandReaderStruct commands[MAX_OUTPUT];
    int commandCounter = 0;
};

#endif //KSPCONTROLLER_FIRMWARE_COMMANDREADER_H

//
// Created by louis on 30/05/19.
//

#include "CommandReader.h"


CommandReader::CommandReader(Stream *_stream) {
    this->stream = _stream;
}

void CommandReader::addOutput(CommandReaderStruct commandReaderStruct) {
    commandCounter++;
    commands[commandCounter] = commandReaderStruct;
}

void CommandReader::addOutput(const char *command, void (*callback)(int, String*)) {
    CommandReaderStruct _command;
    _command.command = command;
    _command.callback = callback;
    addOutput(_command);
}

void CommandReader::addOutput(String command, void (*callback)(int, String*)) {
    addOutput(command.c_str(), callback);
}

void CommandReader::process() {
    while (stream->available())
    {
        char letter = stream->read();
        if(letter == '\n') {
            //get command from buffer
            String data;
            for (int i = 0; i < pointer; ++i) {
                data += buffer[i];
            }
            //Separate command et params
            StringSplitter splitter(data, ';', 3);
            int count = splitter.getItemCount();

            String command = splitter.getItemAtIndex(0);
            String params[count-1];
            for (int j = 1; j < count; ++j) {
                params[j] = splitter.getItemAtIndex(j);
            }

            for (int k = 0; k < commandCounter; ++k) {
                //If command correspond then callback
                if(strcmp(commands[k].command, command.c_str()) ){
                    commands[k].callback(count-1, params);
                }
            }
        }
        else {
            buffer[pointer] = letter;
            pointer++;
        }
    }
}
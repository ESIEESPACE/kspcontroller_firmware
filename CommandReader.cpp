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
    //stream->println(String(commandCounter, DEC));
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
    while (stream->available()>0)
    {
        char letter = stream->read();
        if(letter == '\n') {
            //get command from buffer
            int sep = 0;
            for (int i = 0; i < buffer.length(); ++i) {
                if(buffer.charAt(i) == ';') sep++;
            }

            String params[sep];
            String command = (sep == 0 ? buffer : buffer.substring(0, buffer.indexOf(';')));

            buffer.replace(command, "");
            String paramBuffer;
            int sepCount = 0;
            for (int i = 1; i < buffer.length() + 1; ++i) {
                if(buffer.charAt(i) == ';' || i == buffer.length()) {
                    params[sepCount] = paramBuffer;
                    sepCount++;
                    paramBuffer = "";
                }
                else paramBuffer += buffer.charAt(i);
            }
            buffer = "";
            for (int k = 0; k < MAX_OUTPUT; ++k) {
                //If command correspond then callback
                if(String(commands[k].command) == command){
                    commands[k].callback(sep, params);
                    return;
                }
            }
        }
        else {
            buffer += letter;
        }
    }
}
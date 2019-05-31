// MemoryFree library based on code posted here:
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1213583720/15
// Extended by Matthew Murdoch to include walking of the free list.

#ifndef	MEMORY_FREE_H
#define MEMORY_FREE_H

class MemoryFree{
public:
    static unsigned int freeMemory();

private:
    static int freeListSize();
};

#endif
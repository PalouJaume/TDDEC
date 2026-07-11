#include "IO.h"

void IO_Write(ioAddress addr, ioData data)
{
    ioData *p = 0;
    *(p + addr) = data;
}

ioData IO_Read(ioAddress addr)
{
    ioData *p = 0;
    return *(p + addr);
}
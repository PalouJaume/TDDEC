#include "CircularBuffer.h"
#include <stdlib.h>
#include <memory.h>

CircularBuffer* CircularBuffer_Create(void)
{
    void* ptr = malloc(1);
    return ptr;
}

void CircularBuffer_Destroy(void)
{
}

uint8_t CircularBuffer_Write(CircularBuffer* dst, int src)
{
    return 1;
}

int CircularBuffer_Peek(CircularBuffer* dst)
{
    return 1;
}

int CircularBuffer_Read(CircularBuffer* dst)
{
    return 1;
}


#include "stdint.h"

#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

typedef struct CircularBuffer
{
    /* data */
} CircularBuffer;

CircularBuffer* CircularBuffer_Create(void);
void CircularBuffer_Destroy(void);
uint8_t CircularBuffer_Write(CircularBuffer* dest, int src);
int CircularBuffer_Peek(CircularBuffer* dest);
int CircularBuffer_Read(CircularBuffer* dest);

#endif  /* D_CircularBuffer_H */
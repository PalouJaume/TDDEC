#include "stdint.h"

#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

#define MAX_BUFFER_SIZE 100

typedef struct CircularBuffer
{
    // Control - data
    uint8_t head;
    uint8_t tail;
    int8_t *buff;
    uint8_t cnt;
    uint8_t size;
} CircularBuffer;

CircularBuffer* CircularBuffer_Create(uint8_t size);
void CircularBuffer_Destroy(CircularBuffer* buffer);
uint8_t CircularBuffer_Write(CircularBuffer* dst, int src);
int8_t CircularBuffer_Peek(CircularBuffer* dst);
int8_t CircularBuffer_Read(CircularBuffer* dst);
int8_t CircularBuffer_IsEmpty(CircularBuffer* dst);
int8_t CircularBuffer_IsFull(CircularBuffer* dst);
void CircularBuffer_Print(CircularBuffer* buffer);

#endif  /* D_CircularBuffer_H */
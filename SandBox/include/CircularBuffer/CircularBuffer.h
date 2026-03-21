#include "stdint.h"

#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

#define MAX_BUFFER_SIZE 5

typedef struct CircularBuffer
{
    // Control - data
    uint8_t head;
    uint8_t tail;
    int8_t buff[MAX_BUFFER_SIZE];
    uint8_t cnt;
} CircularBuffer;

CircularBuffer* CircularBuffer_Create(void);
void CircularBuffer_Destroy(void);
uint8_t CircularBuffer_Write(CircularBuffer* dst, int src);
int8_t CircularBuffer_Peek(CircularBuffer* dst);
int8_t CircularBuffer_Read(CircularBuffer* dst);
int8_t CircularBuffer_IsEmpty(CircularBuffer* dst);
int8_t CircularBuffer_IsFull(CircularBuffer* dst);

#endif  /* D_CircularBuffer_H */
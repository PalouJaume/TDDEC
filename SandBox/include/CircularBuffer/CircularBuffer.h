#include "stdint.h"

#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

#define MAX_BUFFER_SIZE 100

typedef struct CircularBuffer
{
    // Control - data
    uint8_t head;
    uint8_t tail;
    uint8_t *buff;
    uint8_t cnt;
    uint8_t size;
} CircularBuffer;

typedef struct BufferFmt BufferFmt;

typedef char *(*ColumnFormat)(BufferFmt fmt, uint8_t value, int first);

struct BufferFmt
{
    uint8_t characters_per_line;
    uint8_t character_per_column;
    ColumnFormat cfmt;
};

CircularBuffer* CircularBuffer_Create(uint8_t size);
void CircularBuffer_Destroy(CircularBuffer* buffer);
uint8_t CircularBuffer_Write(CircularBuffer* dst, int src);
int8_t CircularBuffer_Peek(CircularBuffer* dst);
int8_t CircularBuffer_Read(CircularBuffer* dst);
int8_t CircularBuffer_IsEmpty(CircularBuffer* dst);
int8_t CircularBuffer_IsFull(CircularBuffer* dst);
void CircularBuffer_Print(CircularBuffer* buffer, BufferFmt fmt);

char *ColumnFormat_default(BufferFmt fmt, uint8_t value, int first);
char *ColumnFormat_align(BufferFmt fmt, uint8_t value, int first);

#endif  /* D_CircularBuffer_H */
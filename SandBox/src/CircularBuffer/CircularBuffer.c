#include "CircularBuffer.h"
#include <stdlib.h>
#include <memory.h>

CircularBuffer* CircularBuffer_Create(void)
{
    CircularBuffer* ptr = malloc(sizeof(CircularBuffer));
    if (ptr != NULL) {
        ptr->head = 0;
        ptr->tail = 0;
        memset(ptr->buff, 0, sizeof(ptr->buff));
        ptr->cnt = 0;
    }

    return ptr;
}

void CircularBuffer_Destroy(void)
{
}

static uint8_t increment_internal_pointers(uint8_t ptr, uint8_t max_size)
{
    return (ptr +1) % max_size; 
}

uint8_t CircularBuffer_Write(CircularBuffer* dst, int src)
{
    int8_t output = dst->buff[dst->tail];

    dst->buff[dst->tail] = src;

    dst->tail = increment_internal_pointers(dst->tail, MAX_BUFFER_SIZE);

    dst->cnt++;

    return output;
}

int8_t CircularBuffer_Peek(CircularBuffer* dst)
{
    return dst->buff[dst->head];
}

int8_t CircularBuffer_Read(CircularBuffer* dst)
{
    int output = 0;

    if (!CircularBuffer_IsEmpty(dst))
    {
        output = dst->buff[dst->head];

        dst->head = increment_internal_pointers(dst->head, MAX_BUFFER_SIZE);

        dst->cnt--;
    }

    return output;
}

int8_t CircularBuffer_IsEmpty(CircularBuffer* dst)
{
    return (dst->cnt == 0) ? 1 : 0;
}

int8_t CircularBuffer_IsFull(CircularBuffer* dst)
{
    return (dst->cnt == sizeof(dst->buff)) ? 1 : 0;
}


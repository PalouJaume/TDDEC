#include "CircularBuffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "Utils.h"
#include <string.h>

CircularBuffer *CircularBuffer_Create(uint8_t size)
{
    uint8_t buff_size = (MAX_BUFFER_SIZE < size) ? MAX_BUFFER_SIZE : size;
    CircularBuffer *ptr = malloc(sizeof(CircularBuffer));
    if (ptr != NULL)
    {
        ptr->head = 0;
        ptr->tail = 0;
        ptr->buff = (int8_t *)calloc(buff_size, sizeof(int8_t));
        ptr->cnt = 0;
        ptr->size = buff_size;
    }

    return ptr;
}

void CircularBuffer_Destroy(CircularBuffer *buffer)
{
    if (buffer != NULL)
    {
        if (buffer->buff != NULL)
            free(buffer->buff);

        free(buffer);
        buffer = NULL;
    }
}

static uint8_t increment_internal_pointers(uint8_t ptr, uint8_t max_size)
{
    return (ptr + 1) % max_size;
}

uint8_t CircularBuffer_Write(CircularBuffer *dst, int src)
{
    int8_t output = dst->buff[dst->tail];

    dst->buff[dst->tail] = src;

    dst->tail = increment_internal_pointers(dst->tail, dst->size);

    dst->cnt++;

    return output;
}

int8_t CircularBuffer_Peek(CircularBuffer *dst)
{
    return dst->buff[dst->head];
}

int8_t CircularBuffer_Read(CircularBuffer *dst)
{
    int output = 0;

    if (!CircularBuffer_IsEmpty(dst))
    {
        output = dst->buff[dst->head];

        dst->head = increment_internal_pointers(dst->head, dst->size);

        dst->cnt--;
    }

    return output;
}

int8_t CircularBuffer_IsEmpty(CircularBuffer *dst)
{
    return (dst->cnt == 0) ? 1 : 0;
}

int8_t CircularBuffer_IsFull(CircularBuffer *dst)
{
    return (dst->cnt == dst->size) ? 1 : 0;
}

static char *compose_array(CircularBuffer *buffer)
{
    unsigned int size = 1;
    uint8_t cnt = 0;
    char *array = (char *)malloc(size * sizeof(char));
    if (array == NULL)
        goto error;
    memset(array, '\0', size);

    for (uint8_t i = buffer->head;
         (i != buffer->tail || cnt != buffer->cnt) && buffer->cnt > 0;
         i = increment_internal_pointers(i, buffer->size))
    {
        char value[5] = "";

        if (i != buffer->head)
            snprintf(value, 5, ", %d", buffer->buff[i]);
        else
            snprintf(value, 5, "%d", buffer->buff[i]);

        value[4] = '\0';

        unsigned int new_size = size + strnlen(value, 5);
        array = (char *)realloc(array, new_size * sizeof(char));
        if (array == NULL)
            goto error;

        strncat(array, value, new_size);
        size = new_size;
        cnt++;
    }

    return array;
error:
    if (array != NULL)
        free(array);
    return NULL;
}

void CircularBuffer_Print(CircularBuffer *buffer)
{
    char *array = NULL;

    array = compose_array(buffer);

    FormatOutput("Circular buffer content:\n<%s>\n", (array != NULL) ? array : "");

    free(array);
}

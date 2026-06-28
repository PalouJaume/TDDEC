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
        ptr->buff = (uint8_t *)calloc(buff_size, sizeof(uint8_t));
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

static char *compose_array(CircularBuffer *buffer, BufferFmt fmt)
{
    char *array = NULL;
    size_t size = 0;
    size_t rows = 0;

    uint8_t cnt = 0;
    for (uint8_t i = buffer->head;
         (i != buffer->tail || cnt != buffer->cnt) && buffer->cnt > 0;
         i = increment_internal_pointers(i, buffer->size))
    {
        char *tmp = NULL;

        char *value = fmt.cfmt(fmt, buffer->buff[i], i == buffer->head);

        size_t characters_in_line = size + strnlen(value, 5) - 1 - rows * fmt.characters_per_line;

        if (characters_in_line > fmt.characters_per_line)
        {
            tmp = (char *)realloc(array, (size + 2) * sizeof(char));
            if (tmp == NULL)
                goto error;

            array = tmp;

            array[size] = '\n';
            array[size + 1] = '\0';

            size = strlen(array);
            rows++;
        }

        size_t new_size = size + 1 + strnlen(value, 5) + 1;

        tmp = (char *)realloc(array, new_size * sizeof(char));
        if (tmp == NULL)
            goto error;

        array = tmp;

        if (size == 0)
            memset(array, '\0', size);

        strncat(array, value, new_size);
        size = strlen(array);
        cnt++;

        free(value);
    }

    return array;
error:
    if (array != NULL)
        free(array);
    return NULL;
}

void CircularBuffer_Print(CircularBuffer *buffer, BufferFmt fmt)
{
    char *array = NULL;

    array = compose_array(buffer, fmt);

    FormatOutput("Circular buffer content:\n<%s>\n", (array != NULL) ? array : "");

    if (array != NULL)
        free(array);
}

char *ColumnFormat_default(BufferFmt fmt, uint8_t value, int first)
{
    char *column = (char *)calloc(5, sizeof(char));
    if (column == NULL)
        return NULL;

    if (first == 0)
        snprintf(column, 5, ", %d", value);
    else
        snprintf(column, 5, "%d", value);

    column[4] = '\0';

    return column;
}

// TODO: Refactorizar y repensar la estructura de datos
char *ColumnFormat_align(BufferFmt fmt, uint8_t value, int first)
{
    size_t c_size = (first == 1) ? fmt.character_per_column + 1 : fmt.character_per_column + 2;

    char *column = (char *)calloc(c_size, sizeof(char));
    if (column == NULL)
        goto error_column;

    char *num = (char *)calloc(4, sizeof(char));
    if (num == NULL)
        goto error_num;

    snprintf(num, 4, "%u", value);

    int i = strnlen(num, 4) - 1;
    int j = c_size - 2;

    while (j >= 0)
    {
        if (i >= 0)
        {
            column[j] = num[i];
            i--;
        }
        else
        {
            column[j] = ' ';
        }
        j--;
    }

    if (first != 1)
        column[0] = ',';

    free(num);

    return column;
error_num:
    free(column);
error_column:
    return NULL;
}
#include "FormatOutputSpy.h"

#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"

static char *spyBuff = NULL;
static size_t spySize = 0;
static int spyBuff_offset = 0;
static int spyBuff_used = 0;

void FormatOutputSpy_Create(size_t size)
{
    FormatOutputSpy_Destroy();
    spySize = size + 1;
    spyBuff = (char *)calloc(spySize, sizeof(char));
    spyBuff_offset = 0;
    spyBuff_used = 0;
}

void FormatOutputSpy_Destroy()
{
    if (spyBuff != NULL)
    {
        free(spyBuff);
        spyBuff = NULL;
        spySize = 0;
        spyBuff_offset = 0;
        spyBuff_used = 0;
    }
}

int FormatOutputSpy(const char *fmt, ...)
{
    int written_size;
    va_list arguments;
    va_start(arguments, fmt);
    written_size = vsnprintf(spyBuff + spyBuff_offset,
                             spySize - spyBuff_used,
                             fmt,
                             arguments);
    spyBuff_offset += written_size;
    spyBuff_used += written_size;
    va_end(arguments);
    return 1;
}

char *FormatOutputSpy_GetOutput()
{
    return spyBuff;
}
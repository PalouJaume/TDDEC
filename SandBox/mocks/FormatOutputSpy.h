#ifndef D_FORMATOUTPUTSPY_H
#define D_FORMATOUTPUTSPY_H

#include "Utils.h"
#include "stdlib.h"

int FormatOutputSpy(const char *fmt, ...);

void FormatOutputSpy_Create(size_t size);
void FormatOutputSpy_Destroy();

char *FormatOutputSpy_GetOutput();

#endif /* D_FORMATOUTPUTSPY_H */
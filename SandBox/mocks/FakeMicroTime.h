#ifndef D_FAKEMICROTIME_H
#define D_FAKEMICROTIME_H

#include <stdint.h>

#include "MicroTime.h"

void FakeMicroTime_Init(uint32_t start, uint32_t incr);

#endif /* D_FAKEMICROTIME_H */
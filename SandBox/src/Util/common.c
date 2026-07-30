#include "common.h"
#include <assert.h>

void explodesInTestEnvironment(void *p)
{
    assert(0 == "Explode - intercepted call that cannot be made in test environment");
}
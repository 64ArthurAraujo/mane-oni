#include "string.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char* strdup(const char *__s)
{
        char *dup = malloc(strlen(__s) + 1);

    if (dup != NULL)
       strcpy(dup, __s);

    return dup;
}
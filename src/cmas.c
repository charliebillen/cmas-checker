#include <time.h>

#include "cmas.h"

int cmas()
{
    time_t t = time(NULL);
    struct tm *dt = localtime(&t);

    return (dt->tm_mday == 25 && dt->tm_mon == 11);
}

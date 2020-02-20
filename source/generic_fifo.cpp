#include "generic_fifo.h"


bool Generic_fifo::is_empty()
{
    return (size_actual() == 0);
}

bool Generic_fifo::is_full()
{
    return (size_actual() == size_max());
}

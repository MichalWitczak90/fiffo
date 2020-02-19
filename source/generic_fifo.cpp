#include "generic_fifo.h"

Generic_fifo::Generic_fifo(int size_actual, int size_max) 
:
_size_actual(size_actual),
_size_max(size_max)
{

}

Generic_fifo::~Generic_fifo()
{

}

int Generic_fifo::size_actual()
{
    return _size_actual;
}

int Generic_fifo::size_max()
{
    return _size_max;
}

bool Generic_fifo::is_empty()
{
    return (_size_actual == 0);
}

bool Generic_fifo::is_full()
{
    return (_size_actual == _size_max);
}

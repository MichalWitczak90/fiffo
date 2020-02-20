#ifndef _generic_fifo_h
#define _generic_fifo_h

/*
* project:	fifo
* file:		generic_fifo.h
* author:	en2
* date:		19-02-2020
*/

class Generic_fifo
{
public:
    virtual int size_actual() = 0;
    virtual int size_max() = 0;

    bool is_empty();
    bool is_full();

}; /* class: Generic_fifo */

#endif /*define: generic_fifo_h*/
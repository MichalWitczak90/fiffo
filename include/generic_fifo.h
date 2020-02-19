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
    Generic_fifo(int size_actual, int size_max);
    ~Generic_fifo();

    int size_actual();
    int size_max();

    bool is_empty();
    bool is_full();

    virtual int size_item() = 0;
    virtual int size_total() = 0;
    virtual void push(void * from) = 0;
    virtual void pop(void * to) = 0;

protected:
    int _size_actual;
    int _size_max;

private:
    

}; /* class: Generic_fifo */

#endif /*define: generic_fifo_h*/
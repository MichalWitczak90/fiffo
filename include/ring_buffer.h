#ifndef _ring_buffer_h
#define _ring_buffer_h

/*
* project:	fifo
* file:		ring_buffer.h
* author:	en2
* date:		19-02-2020
*/

#include "generic_fifo.h"

template<typename T = int, int size = 32>
class Ring_buffer : public Generic_fifo
{
public:
    Ring_buffer();
    ~Ring_buffer();

    void push(const T & item);
    T pop();

    int index_front();
    int index_back();

    int size_item();
    int size_total();
    void push(void * from);
    void pop(void * to);

protected:
    

private:
    T _item[size];
    int _head;

}; /* class: Ring_buffer */

template<typename T, int size>
Ring_buffer<T, size>::Ring_buffer()
:
Generic_fifo(0, size),
_head(0)
{

}

template<typename T, int size>
Ring_buffer<T, size>::~Ring_buffer()
{

}

template<typename T, int size>
void Ring_buffer<T, size>::push(const T & item)
{
    _item[_head] = item;
    _head = (_head + 1) % size;

    if (_size_actual < size) _size_actual++;
}

template<typename T, int size>
T Ring_buffer<T, size>::pop()
{
    if (_size_actual)
    {
        auto temp = _item[index_front()];
        _size_actual--;
        return temp;
    }   
    else return {};
}

template<typename T, int size>
int Ring_buffer<T, size>::index_front()
{
    return (_head >= _size_actual) ? _head - _size_actual : _head + size - _size_actual;
}

template<typename T, int size>
int Ring_buffer<T, size>::index_back()
{
    return (_head != 0) ? _head - 1 : size - 1;
}

template<typename T, int size>
void Ring_buffer<T, size>::push(void * from)
{
    auto * ptr = static_cast<T *>(from);
    push(*ptr);
}

template<typename T, int size>
void Ring_buffer<T, size>::pop(void * to)
{
    auto * ptr = static_cast<T *>(to);
    *ptr = pop();
}

template<typename T, int size>
int Ring_buffer<T, size>::size_item()
{
    return sizeof(T);
}

template<typename T, int size>
int Ring_buffer<T, size>::size_total()
{
    return sizeof(Ring_buffer<T, size>);
}

#endif /*define: ring_buffer_h*/
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

    void push(T item);
    T pop();

    int size_actual();
    int size_max();

protected:
    int _index_front();
    int _index_back();    

private:
    int _size_actual;
    T _item[size];
    int _head;

}; /* class: Ring_buffer */

template<typename T, int size>
Ring_buffer<T, size>::Ring_buffer()
:
_size_actual(0),
_head(0)
{

}

template<typename T, int size>
Ring_buffer<T, size>::~Ring_buffer()
{

}

template<typename T, int size>
void Ring_buffer<T, size>::push(T item)
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
        auto temp = _item[_index_front()];
        _size_actual--;
        return temp;
    }   
    else return {};
}

template<typename T, int size>
int Ring_buffer<T, size>::_index_front()
{
    return (_head >= _size_actual) ? _head - _size_actual : _head + size - _size_actual;
}

template<typename T, int size>
int Ring_buffer<T, size>::_index_back()
{
    return (_head != 0) ? _head - 1 : size - 1;
}

template<typename T, int size>
int Ring_buffer<T, size>::size_actual()
{
    return _size_actual;
}

template<typename T, int size>
int Ring_buffer<T, size>::size_max()
{
    return size;
}

#endif /*define: ring_buffer_h*/
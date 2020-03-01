#ifndef _measurements_h
#define _measurements_h

/*
* project:	fifo
* file:		measurements.h
* author:	en2
* date:		01-03-2020
*/

#include <chrono>
#include<type_traits>

using Time = std::chrono::microseconds;

template<typename F>
long int measure(F functor, int iterations)
{
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < iterations; i++)
    {
        functor();
    }

    return std::chrono::duration_cast<Time>(std::chrono::steady_clock::now() - start).count();
}


#endif /*define: measurements_h*/
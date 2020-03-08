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

/**
 * @brief Funkcja pomiaru czasu wykonania
 *
 * @param[in] functor lambda funkcji ktora bedzie podlegala sprawdzeniu
 * @param[in] iterations liczba iteracji wywolania funktora
 * @return czas egzekucji [n] iteracji funktora w jednostce [us]
 * 
 * Funkcja w swojej implementacji wykorzystuje biblioteke chrono, w celu 
 * dwukrotnego pobrania aktualnego czasu w systemie (przed i po wykonaniu
 * [n] iteracji funktora).
 * 
 * Wykorzystanie funktora pozwala na zastosowanie jednej funkcji pomiarowej
 * niezaleznie od typu kontenera oraz formy wywolania jego metody.
**/

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
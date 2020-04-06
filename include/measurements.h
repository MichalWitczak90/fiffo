#ifndef _measurements_h
#define _measurements_h

/**
 * @file	measurements.h
 * @author	Michal Witczak
 * @date	06-04-2020
 * @brief	
 * @details	
**/

#include <chrono>
#include<type_traits>

using Time = std::chrono::microseconds;

/**
 * @brief	Generyczna metoda pomiaru czasu wykonania.
 * @tparam  functor Funktor ktory bedzie poddany pomiarowi	.
 * @param	iterations Ilosc iteracji wywolania funktora podczas pomiaru.
 * @return	Czas [us] n-iteracji wywolania zadanego funktora.
 * @details	Implementacyjne, metoda wykorzystuje biblioteke <chrono> (pobranie aktualnego czasu
 *          przez rozpoczeciem iteracji funktora, oraz pobranie czasu po zakonczeniu iteracji). 
 *          Wykorzystanie funktora (czyli obiektu ktory moze byc wywolany jak zwykla funkcja) pozwoli
 *          na zachowanie generycznosci metody oraz stworzenie warstwy abstrakcji od testowanych kontenerow
 *          (ze wzgledu na roznice w nazewnictwie metod poszczegolnych kontenerow) - funktor opisuje wiec
 *          pojedyncza "rzecz" podlegajaca sprawdzeniu, abstrachujac od jej postaci czy wywolania.
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


#endif /* define: measurements_h */
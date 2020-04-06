#ifndef _ring_buffer_h
#define _ring_buffer_h

/**
 * @file	ring_buffer.h
 * @author	Michal Witczak
 * @date	06-04-2020
 * @brief	
 * @details	
**/

#include "generic_fifo.h"

template<typename T = int, int size = 32>
class Ring_buffer : public Generic_fifo
{
    /**
     * @class	Ring_buffer
     * @brief	Bufor kolowy bedacy implementacja kolejki FIFO.
     * @details	Klasa symbolizujaca bufor kolowy. Jednym z jego podstawowych zasosowan moze byc np. 
     *          odbior oraz przechowywanie danych w dostarczanych przez sterownik ukladu peryferyjnego
     *          w systemie wbudowanym (mikroprocesor). Z uwagi na fakt, iz tego typu sterowniki dzialaja
     *          niskopoziomowo (najczesciej w formie przerwania IRQ procesora), w celu gromadzenia danych
     *          niezbedny jest kontener o szybkim i staloczasowym dostepnie do poszczegolnego elementu.
     *          Implementacja bufora kolowego obejmuje nadpisanie najstarszego elementu w przypadku 
     *          przepelnienia kolejki, oraz trywialna metode obslugi bledu podczas proby pobrania elementu
     *          z pustego bufora (wartosc ma charakter udefined oraz stanowi domyslny konstruktor zadanego
     *          typu). 
    **/
public:
    Ring_buffer();
    ~Ring_buffer();

    /**
     * @brief	Dodanie elementu do bufora.
     * @param	item Element do umieszczenia w buforze.
     * @return	
     * @details	Element przekazany do metody zostaje umieszczony w buforze na pozycji wskazywanej przez
     *          index _head. Indeks ten nastepnie zostaje zwiekszony, oraz sprawdzony pod katem zgodnosci
     *          z rozmiarem kontenera podanym w szablonie (operacja modulo). Jezeli kontener nie osiagnal
     *          jeszcze swojej maksymalnej wartosci, zmienna _size_actual zostaje zwiekszona (jednak
     *          do wartosci nie wiekszej niz zadany rozmiar kontenera) - co jest zgodne z teoria
     *          zasady dzialania bufora kolowego. 
    **/
    void push(T item);

    /**
     * @brief	Zdejmowanie elementu z bufora.
     * @return	Wartosc elementu.
     * @details	Element wyciagany z bufora kolowego jest elementem najstarszym (tym ktory zostal dodany
     *          najpozniej). Jego indeks obliczany jest na podstawie aktualnego wskaznika nastepnego elementu
     *          (zmienna _head), oraz aktualnej zajetosci bufora (zmienna _size_actual). Po pobraniu,
     *          rozmiar bufora zostaje zmniejszony (nie ma koniecznosci przesuwania indeksu). W przypadku
     *          proby poprania elementu z pustego bufora, metoda nie wzraca wyjatku a jedynie domyslny
     *          konstruktor typu wskazanego przez uzytkownika na poziomie szablonu.
    **/
    T pop();

    /**
     * @brief	Metoda wyliczajaca aktualny poziom zapelnienia bufora.
     * @return	Wartosc zapelnienia.
     * @details	Dzialanie metody polega jedynie na zwracaniu wewnetrzengo pola _size_actual, ktore 
     *          to aktualizowane jest podczas dodawania oraz zdejmowania elementow z bufora. 
     *          Wartosc tego pola nie moze przekroczyc rozmiaru zadanego jako parametr szablonu.
    **/ 
    int size_actual();

    /**
     * @brief	Metoda zwracajaca maksymalny rozmiar bufora.
     * @return	Wartosc rozmiaru bufora.
     * @details	Metoda dziala w oparciu o zwracanie rozmiaru podanego jako parametr szablonu, znanego juz
     *          na etapie kompilacji.
    **/
    int size_max();

protected:
    /**
     * @brief	Metoda wyliczajaca indeks najstarszego elementu.    
     * @return	Indeks najstarszego elementu.
     * @details	Front bufora (czyli element ktory zostal do niego dodany najwczesniej) znajduje sie
     *          w tablicy _item[] pod indeksem ktory wyliczany jest na podstawie pol _size_actual
     *          oraz _head. Podczas jego wyliczania nalezy pamietac o okresowym zawijaniu sie bufora
     *          (czyli nadpisywaniu najstarszych znajdujacych sie w nich elementow).
    **/
    int _index_front();

    /**
     * @brief	Metoda wyliczajaca indeks najmlodszego elementu.
     * @return	Indeks najmlodszego elementu.
     * @details	Koniec bufora (czyli element ktory zostal do niego dodany najpozniej) znajduje sie 
     *          dokladnie jeden element wczesniej niz wskazuje pole _head. W przypadku gdy pole _head
     *          wskazuje na indeks 0, nalezy pamietac o zawijaniu bufora (w tym przypadku najmlodszy element)
     *          znajduje sie na ostatniej pozycji tablicy _item[]). 
    **/
    int _index_back();    

private:
    int _size_actual;   /**< Aktualna zajetosc bufora */
    T _item[size];      /**< Tablica przechowujaca koeljne elementy umieszczanie w buforze */
    int _head;          /**< Wskaznik umieszczenia nastepnego elementu */

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

#endif /* define: ring_buffer_h */
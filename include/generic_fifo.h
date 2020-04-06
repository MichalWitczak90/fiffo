#ifndef _generic_fifo_h
#define _generic_fifo_h

/**
 * @file	generic_fifo.h
 * @author	Michal Witczak
 * @date	06-04-2020
 * @brief   
 * @details  
**/

class Generic_fifo
{
    /**
     * @class	Generic_fifo
     * @brief	Interfejs do zbioru klas symbolizujacych kolejke fifo.
     * @details	Ze wzgledu na wykorzystanie metod czysto wirtualnych, interfejs staje sie klasa 
     *          abstrakcyjna. Interfejs reprezentuje generyczna kolejke zbioru wartosci dowolnego typu,
     *          oraz na tym etapie odnosi sie jedynie do jego rozmiaru czy tez zajetosci. Metody 
     *          wirtualne zostana uzupelnione w klasach potomnych na podstawie swojej wewnetrznej implementacji.
     *          Warto zwrocic uwage, iz wartosci przedstawiajace aktualny oraz maksymalny rozmiar nie musza
     *          byc przechowywane jako pola klasy - mozna sobie wyobrazic implementacje kolejki ktora wylicza
     *          wartosc zajetosci na podstawie innych pol. 
    **/
public:
    Generic_fifo();
    ~Generic_fifo();

    /**
     * @brief	Metoda wyliczajaca aktualny rozmiar kolejki FIFO.
     * @return	Aktualny rozmiar kolejki.
     * @details	
    **/
    virtual int size_actual() = 0;

    /**
     * @brief	Metoda wyliczajaca maksymalny rozmiar kolejki FIFO.
     * @return	Maksymalny rozmiar kolejki.
     * @details	
    **/
    virtual int size_max() = 0;

    /**
     * @brief	Metoda sprawdzajaca czy kolejka FIFO jest pusta.
     * @return	true - Kolejka jest pusta, false - Kolejka nie jest pusta. 
     * @details	Metoda dziala jedynie w oparciu o wykorzystanie funkcji abstrakcyjnej (jezeli aktualna 
     *          zajetosc koeljki wynosi 0, oznacza to ze kolejka jest pusta).
    **/
    bool is_empty();

    /**
     * @brief	Metoda sprawdzajaca czy kolejka FIFO jest pelna.
     * @return	true - Kolejka jest pelna, false - Kolejka nie jest pelna.
     * @details	Metoda dziala jedynie w oparciu o wykorzystanie funkcji abstrakcyjnych (jezeli aktualna
     *          zajetnosc kolejki jest rowna maksymalnej mozliwej zawartosci, oznacza to ze kolejka
     *          jest pelna).
    **/
    bool is_full();

}; /* class: Generic_fifo */

#endif /* define: generic_fifo_h */

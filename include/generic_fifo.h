#ifndef _generic_fifo_h
#define _generic_fifo_h

/*
* project:	fifo
* file:		generic_fifo.h
* author:	en2
* date:		19-02-2020
*/

/**
 * \class Generic_fifo
 * \brief Abstrakcyjna klasa bazowa generycznego kontenera
 * 
 * Klasa jest reprezentacja kontenera ktory bedzie przechowywal elementy nieznanego na tym etapie
 * dziedziczenia typu (typ danych zostanie nadany jako typ szablonowy w klasach potomnych). 
 * 
 * Klasa posiada posiada dwie metody "czysto" wirtualne (powiazane z rozmiarem kontenera, ktory 
 * podobnie jak w przypadku typu nie jest jeszcze znany) ktore zostana uzupelnione w klasach 
 * potomnych. Tego typu podejscie pozwoli na wykorzystanie polimorfizmu tj. mozliwosci przypisania
 * wskaznikow na klasy potomne do wskaznika na klase bazowa. Dodatkowo, na tym etapie kompilacji
 * nie jestesmy w stanie okreslic, ani tez nie chcemy wymuszac koniecznosci przechowywania wartosci 
 * rozmiaru aktualnego przez klasy potomne (ktora moze byc np. wyliczana na bierzaco - ten
 * mechanizm pozostawiamy implementacji klasy potomnej). 
 * 
 * Klasa posiada rowniez dwie "zwykle" metody odpowiedzialne za zglaszanie stanu kolejki, 
 * ktore kozystaja jendak z metod czysto wirtualnych.
 * 
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
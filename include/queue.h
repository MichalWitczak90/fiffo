#ifndef _queue_h
#define _queue_h

/**
 * @file	queue.h
 * @author	Michal Witczak
 * @date	06-04-2020
 * @brief	
 * @details	
**/

#include "ring_buffer.h"

template<typename T = int>
class Queue : public Generic_fifo
{
    /**
     * @class	Queue
     * @brief	Kolejka FIFO z mozliwoscia automatycznego zwiekszania.
     * @details	Wewnetrzna implementacja kolejki wykorzystuje zaprojektowany uprzednio bufor kolowy
     *          (bedacy typem bazowym o rozmiarze 1024), ktory obudowany zostal w system pojedynczo
     *          laczonej listy (single-linked list) posiadajacej wezly. Kazdy wezel to tak naprawde
     *          pojedynczy bufor kolowy o rozmiarze 1024 - w przypadku gdy aktualny wezel ulegnie zapelnieniu
     *          w calosci - powolywany jest kolejny (oraz laczony z poprzednim). Analogicznie jezeli 
     *          podczas usuwania elementow z kolejki aktualny wezel zostanie w pelni oprozniony, jest on
     *          usuwany oraz zastepowany wezlem ktory jest jego rodzicem. 
    **/

    static constexpr auto size_internal = 1024;     /**< Rozmiar pojedynczego bufora kolowego */
    using Block = Ring_buffer<T, size_internal>;    /**< Typ bufora kolowego */
    struct Node {Block * block; Node * parent;};    /**< Struktora pojedynczego wezla */

public:
    Queue();
    ~Queue();

    /**
     * @brief	Metoda dodajaca element do kolejki. 
     * @param	item Wartosc elementu ktory ma zostac dodany.
     * @return	
     * @details	Implementacja metody bazuje na sprawdzeniu czy w aktualnym wezle (czyli aktualnym buforze
     *          kolowym) znajduje sie jeszcze miejsce na nowy element. Jezeli tak, jest on umieszczany
     *          bezposrednio, w przypadku gdy aktualny bufor jest juz w pelni zajety, w celu unikniecia 
     *          jego nadpisania zostaje wywolana metoda _allocate(), ktora odpowiedzialna jest na 
     *          dynamiczne utworzenie nowego bufora, ktory przejmuje wskazany element do zapisania.
    **/
    void push(T item);

    /**
     * @brief	Metody zdejmujaca element z kolejki.
     * @return	Wartosc elementu.
     * @details	Metoda dziala przeciwnie do metody push(). W pierwszym kroku, metoda sprawdza czy w kolejce
     *          znajduje sie element do zdjecia (poprzez wywolanie metody size_actual()). W zwiazku z faktem,
     *          iz pop zawsze zwraca element najstarszy - istnieje szansa ze znajduje sie on poza aktualnym
     *          buforem kolowym (np przy wywolaniu 1024 razy metody push() - buforem aktualnym bedzie w 
     *          w tym przypadku pusty bufor, natomiast buforem rodzicem - bufor ktory przechowuje 1024
     *          nowo dodane wartosci.). W tym przypadku istnieje koniecznosc znalezienia najstarszego
     *          powolanego do zycia bufora (za co odpowiedzialna jest metoda _root_find()), pobrania z niego
     *          elementu oraz usunieciu bufora w przypadku gdy jest on calkowicie pusty.
    **/
    T pop();

    /**
     * @brief	Metoda wzracajaca aktualny rozmiar kolejki.
     * @return	Aktualny rozmiar kolejki.
     * @details	Implementacja metody bazuje na znajomosci wszystkich powolanych do zycia buforow 
     *          oraz sprawdzeniu ich aktualnej zajetosci (ze wzgledu na fakt, iz kolejka teoretycznie rosnie
     *          w nieskonczonosc, metoda musi sprawdzic wszystkie wezly bedace buforami kolowymi oraz
     *          dokonac sumowania ich elementow. 
    **/
    int size_actual();

    /**
     * @brief	Metoda zwracajaca maksymalny rozmiar kolejki.
     * @return	-1 
     * @details	Ze wzlgedu na fakt, iz kolejka "rosnie" w nieskonczonosc, metoda zwraca -1.
    **/
    int size_max();

protected:
    /**
     * @brief	Powolanie nowego bufora kolowego.
     * @return	
     * @details	W przypadku calkowitej zajetosci aktualnego wezla, istnieje koniecznosc powolania do zycia
     *          nowego, pustego wezla. Po jego dynamicznym powolaniu, metoda dokonuje jego dowiazania do
     *          istniejacego drzewa wezlow jako kolejnego elementow (uzupelniajac pola bedaca wskaznikiem)
     *          na rodzica wezla, oraz zmieniajac wskaznik na aktualny wezel (ktorym staje sie wezel nowoutworzony).
    **/
    void _allocate();

    /**
     * @brief	Zwolnienie najstarszego bufora kolowego.
     * @return	
     * @details	W przypadku calkowitego zwolnienia bufora ktory przechowuje najstarsze elementy, istnieje
     *          koniecznosc jego zwolnienia. Metoda dokonuje jego dealokacji oraz przerwania polaczen 
     *          ktore moga do niego doprowadzic w drzewie wezlow.
    **/
    void _deallocate();

    /**
     * @brief	Poszukiwanie poczatku drzewa.
     * @return	Wskaznik na poczatek drzewa wezlow.
     * @details	Metoda dokonuje przeszukiwania drzewa od wezla aktualnego (najmlodszego), do wskaznika 
     *          na wezel najstarszy.
    **/
    Node * _root_find();

private:
    Node * _node;       /**< Wskaznik na aktualny wezel */

}; /* class: Queue */

template<typename T>
Queue<T>::Queue()
{
    _node = new Node;
    _node->block = new Block;
    _node->parent = nullptr;
}

template<typename T>
Queue<T>::~Queue()
{
    delete _node->block;
    delete _node;

    auto * parent = _node->parent;

    while(parent != nullptr)
    {
        delete parent->block;
        delete parent;

        parent = parent->parent;
    }
}

template<typename T>
void Queue<T>::push(T item)
{
    if (_node->block->is_full()) _allocate();
    
    _node->block->push(item);
}

template<typename T>
T Queue<T>::pop()
{
    if (size_actual() > 0)
    {
        auto * root = _root_find();

        auto temp = root->block->pop();

        if (root->block->is_empty()) _deallocate();

        return temp;
    }
    else return {};
}

template<typename T>
int Queue<T>::size_actual()
{
    auto count = 0;

    count += _node->block->size_actual();

    auto * parent = _node->parent;

    while(parent != nullptr)
    {
        count += _node->parent->block->size_actual();

        parent = parent->parent;
    }

    return count;
}

template<typename T>
int Queue<T>::size_max()
{
    return -1;
}   

//---------------------------------------------| info |---------------------------------------------//

template<typename T>
void Queue<T>::_allocate()
{
    auto * child = new Node;
    child->block = new Block;

    child->parent = _node;
    _node = child;
}

template<typename T>
void Queue<T>::_deallocate()
{
    if (_node->parent != nullptr)
    {
        auto * current = _node;

        while(current->parent->parent != nullptr)
        {
            current = current->parent;
        }

        delete current->parent->block;
        delete current->parent;

        current->parent = nullptr;
    }
}

template<typename T>
typename Queue<T>::Node * Queue<T>::_root_find()
{
    auto * current = _node;

    while(current->parent != nullptr)
    {
        current = current->parent;
    }

    return current;
}

#endif /* define: queue_h */
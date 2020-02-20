#ifndef _queue_h
#define _queue_h

/*
* project:	fifo
* file:		queue.h
* author:	en2
* date:		20-02-2020
*/

#include "ring_buffer.h"

template<typename T = int>
class Queue : public Generic_fifo
{
    static constexpr auto size_internal = 4;
    using Block = Ring_buffer<T, size_internal>;
    struct Node {Block * block; Node * parent;};

public:
    Queue();
    ~Queue();

    void push(const T & item);
    T pop();

    int size_actual();
    int size_max();

protected:
    void _allocate();
    void _deallocate();

    Node * _root_find();

private:
    Node * _node;

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
void Queue<T>::push(const T & item)
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

#endif /*define: queue_h*/
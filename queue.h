#include "circulararray.h"

// FIFO structure

template <typename T>
class QueueArray : public CircularArray<T> { 
public:
    QueueArray() = default;
    T dequeue();
    void enqueue(T data);
    void display();
};

template<typename T>
T QueueArray<T>::dequeue()
{
    this->pop_front();
}

template<typename T>
void QueueArray<T>::enqueue(T data)
{
    this->push_back(data);
}

template<typename T>
void QueueArray<T>::display()
{
    return;
}
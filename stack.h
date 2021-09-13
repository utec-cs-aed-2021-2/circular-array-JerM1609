#include "circulararray.h"

// LIFO structure

template <typename T>
class StackArray : public CircularArray<T> {
public:
    StackArray() = default;     // +
    ~StackArray() = default; 

    void push(T data);          // +
    T pop();                    // +
    void display();             // -
};

template<typename T>
void StackArray<T>::push(T data)
{
    this->push_back(data);
}

template<typename T>
T StackArray<T>::pop()
{
    return this->pop_back();
}

template<typename T>
void StackArray<T>::display()
{
    cout << this->to_string(" ") << endl;
}
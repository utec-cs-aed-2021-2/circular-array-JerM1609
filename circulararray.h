#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();                        // +
    CircularArray(int _capacity);           // 
    virtual ~CircularArray();               // +
    void push_front(T data);                //
    void push_back(T data);                 //
    void insert(T data, int pos);           //
    T pop_front();                          //
    T pop_back();                           //            
    bool is_full();                         //
    bool is_empty();                        //
    int size();                             //
    void clear();                           //
    T &operator[](int index);               //
    void sort();                            //
    bool is_sorted();                       //
    void reverse();                         //
    string to_string(string sep=" ");       // +

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];         // dynamic array in heap
    this->capacity = _capacity;             // assign capacity
    this->front = this->back = -1;          // initialize indirection markers
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template<class T>
void CircularArray<T>::push_front(T data)
{
    // TODO
    return;
}   

template<class T>
void CircularArray<T>::push_back(T data)
{
    // TODO
    return;
}

template<class T>
void CircularArray<T>::insert(T data, int pos)
{
    // TODO
    return;
}

template<class T>
T CircularArray<T>::pop_front()
{  
    // TODO
    return T{};
}

template<class T>
T CircularArray<T>::pop_back()
{
    // TODO
    return T{};
}

template<class T>
bool CircularArray<T>::is_full()
{
    return next(rear) == front;
}

template<class T>
bool CircularArray<T>::is_empty()
{
    return (this->size() == 0);
}

template<class T>
int CircularArray<T>::size()
{
    if (front > back)       // TestCases (f, b) -> (7, 1) (6, 2)
        return this->capacity - (front - back - 1);
    else if (front < back)  // TestCases (f, b) -> (1, 6) (1, 4)    
        return back - front + 1;
    else 
        return 0;
}

template<class T>
void CircularArray<T>::clear()
{

}

template<class T>
T& CircularArray<T>::operator[](int index)
{

}

template<class T>
void CircularArray<T>::sort()
{

}

template<class T>
bool CircularArray<T>::is_sorted()
{

}

template<class T>
void CircularArray<T>::reverse()
{
    
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}

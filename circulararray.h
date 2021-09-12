#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
protected:
    T *array;           // for runtime resizing
    int capacity;       // for table doubling
    int back, front;    // indirection markers
    
public:
    CircularArray();                        // +
    CircularArray(int _capacity);           // 
    virtual ~CircularArray();               // +
    void push_front(T data);                // +
    void push_back(T data);                 // +
    void insert(T data, int pos);           //
    T pop_front();                          //
    T pop_back();                           //            
    bool is_full();                         //
    bool is_empty();                        //
    int size();                             //
    void resize(int new_capacity);
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
    if (this->is_full())      // if last index is filled
        this->resize(capacity * 2);
    front = prev(front);      // go to the previous index
    array[front] = data;      // fill index with new element
}   

template<class T>
void CircularArray<T>::push_back(T data)
{
    if (this->is_full())       // if array is completely full
        this->resize(capacity * 2);
    back = next(back);         // go to the next index
    array[back] = data;        // fill index with new element
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
    if (array == nullptr || this->is_empty())
        return T{};
    T rt_value = array[front];
    front = next(front);
    // estrategia para liberar espacios inutilizados

    return rt_value;
}

template<class T>
T CircularArray<T>::pop_back()
{
    if (array == nullptr || this->is_empty())
        return T{};
    T rt_value = array[back];
    back = prev(back);
    // estrategia para liberar espacios inutilizados
    if (size < capacity/2)
        this->resize(capacity/2);
        
    return rt_value;
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
    //TODO
}

template<class T>
void CircularArray<T>::resize(int new_capacity)
{
    T* new_array = new T[new_capacity];
    for (int i = 0; i < min(capacity, new_capacity); i++)
        new_array[i] = array[i];
    this->capacity = new_capacity;
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

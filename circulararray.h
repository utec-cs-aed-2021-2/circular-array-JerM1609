#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
void swapValue(T *first, T *second)
{
    T valTemp = *first;
    *first = *second;
    *second = valTemp;
    return;
}

template<typename T>
T* Median(T *a, T *b, T *c)
{
    if ((*a < *b && *b < *c) ||
            (*c < *b && *b < *a))
        return b;
    else if ((*b < *a && *a < *c) ||
                (*c < *a && *a < *b))
        return a;
    else return c;
}

template<typename T>
void InsertionSort(T *arr, T *begin, T *end)
{
    int left = begin - arr, right = end - arr;
    T cpos, fpos, celement;
    for (int i = left + 1; i <= right; ++i) {
        celement = arr[i];
        cpos = fpos = i;
        while (celement < arr[cpos - 1] && cpos > left)
        {
            arr[cpos] = arr[cpos - 1];
            fpos = --cpos;
        }
        arr[fpos] = celement;
    }
}

template<typename T>
T* Partition(T *arr, int low, int high)
{
    T pivot = arr[high];
    int i = (low - 1), j = low;

    for (; j <= high - 1 ; j++)
    {
        if (arr[j] < pivot)             // stable
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (arr + i + 1);
}

template<typename T>
void SelectAlgo(T *arr, T *begin, T *end, int depthLimit)
{
    int size = end - begin;

    if (size < 16)
    {
        InsertionSort(arr, begin, end);
        return;
    }

    if (depthLimit == 0)
    {
        make_heap(begin, end + 1);
        sort_heap(begin, end + 1);
        return;
    }

    // optimum way to choose a pivot
    T* pivot = Median(begin, begin + size/2, end);
    cout << "size/2: " << size/2 << " pivot: " <<  *pivot << endl;
    swapValue(pivot, end);

    T* partitionPoint = Partition(arr, begin - arr, end - arr);
    printArray(arr, 20);
    SelectAlgo(arr, begin, partitionPoint - 1, depthLimit - 1);
    SelectAlgo(arr, partitionPoint + 1, end, depthLimit - 1);
    return;
}

template<typename T>
void Introsort(T *arr, T *begin, T *end)
{
    int depthLimit = 2 * log(end - begin);
    SelectAlgo(arr, begin, end, depthLimit);
    return;
}

// ---------------------------------------------------------------------------------

template <class T>
class CircularArray
{
protected:
    T *array;           // for runtime resizing
    int capacity;       // for table doubling
    int back, front;    // indirection markers
    
public:
    CircularArray();                        // +
    CircularArray(int _capacity);           // +
    virtual ~CircularArray();               // +

    void push_front(T data);                // +
    void push_back(T data);                 // +
    void insert(T data, int pos);           //
    T pop_front();                          // +
    T pop_back();                           // +          
    
    bool is_full();                         //
    bool is_empty();                        //
    int size();                             //
    
    void resize(int new_capacity);          // +
    void clear();                           // +
    T &operator[](int index);               // +
    void sort();                            //  
    bool is_sorted();                       // 
    void reverse();                         // +-
    string to_string(string sep=" ");       // +

private:
    int next(int);      // +
    int prev(int);      // +
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
    {
        cerr << "pop_front() method doesn't work because structure is empty\n";
        return T{};
    }
    T rt_value = array[front];
    front = next(front);

    // estrategia para liberar espacios inutilizados
    if (this->size() < capacity/2)
        this->resize(capacity/2);
    return rt_value;
}

template<class T>
T CircularArray<T>::pop_back()
{
    if (array == nullptr || this->is_empty())
    {
        cerr << "pop_back() method doesn't work because structure is empty\n";
        return T{};
    }
    T rt_value = array[back];
    back = prev(back);

    // estrategia para liberar espacios inutilizados
    if (this->size() < capacity/2)
        this->resize(capacity/2);
    return rt_value;
}

template<class T>
bool CircularArray<T>::is_full()
{
    return next(back) == front && prev(front) == back;
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
    delete[] array;
    capacity = 0;
    front = back = -1;
}

template<class T>
T& CircularArray<T>::operator[](int index)
{
    return array[(front + index)%capacity];
}

template<class T>
void CircularArray<T>::sort()
{
    //Introsort();
}

template<class T>
bool CircularArray<T>::is_sorted()
{

}

template<class T>
void CircularArray<T>::reverse()
{
    int sfront = front, sback = sback;
    T temp;
    while (sfront < sback)          // then, change condition
    {
        temp = array[sback];
        array[sback] = array[sfront];
        array[sfront] = temp;
        
        sfront = this->next(sfront);
        sback = this->prev(sback);
    }
    return;
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
    int traverse = front, nback = this->next(back);
    string result = ""; 
    while(traverse != nback)
    {
        result += std::to_string((*this)[traverse]) + sep;
        traverse = this->next(traverse);
    }
    return result;    
}

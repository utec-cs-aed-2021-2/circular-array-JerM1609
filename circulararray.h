#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

template<typename T>
void printArray(T* container, int capacity)
{
    for (int i = 0; i < capacity; i++)
        cout << *(container + i) << " ";
    cout << endl;
} 

// ------------------------------------------------------------------ INTROSORT

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

// ------------------------------------------------------------ CIRCULAR ARRAY

template <class T>
class CircularArray
{
protected:
    T *array;           // for runtime resizing
    int capacity;       // for table doubling
    int back, front;    // indirection markers
    int size_ = 0;
public:
    CircularArray();                        // +
    CircularArray(int _capacity);           // +
    virtual ~CircularArray();               // +

    void push_front(T data);                // +
    void push_back(T data);                 // +
    void insert(T data, int pos);           // -
    T pop_front();                          // +
    T pop_back();                           // +          
    
    bool is_full();                         // +
    bool is_empty();                        // +
    int size();                             // +
    
    void resize(int new_capacity);          // +
    void clear();                           // +
    T &operator[](int index);               // +
    void sort();                            // +
    bool is_sorted();                       // +
    void reverse();                         // +
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
    size_ = 0;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template<class T>
void CircularArray<T>::push_front(T data)
{
    //cout << __PRETTY_FUNCTION__ << " ";
    if (this->is_full())      // if last index is filled
        this->resize(capacity * 2);
    if (size_ == 0 && front < 0)
    {
        front = 1; back = 0;
    }
        
    front = prev(front);      // go to the previous index
    //cout << front << endl;
    array[front] = data;      // fill index with new element
    size_++;
}   

template<class T>
void CircularArray<T>::push_back(T data)
{
    //cout << __PRETTY_FUNCTION__ << " ";
    if (this->is_full())       // if array is completely full
        this->resize(capacity * 2);
    back = next(back);         // go to the next index
    array[back] = data;        // fill index with new element
    size_++;
    if (size_ == 1 && front < 0)
        front = back;
}

template<class T>
void CircularArray<T>::insert(T data, int pos)
{
    if (pos > size_)
    {
        cerr << "value in invalid position\n"; return;
    }
    if (this->is_full())
        this->resize(capacity*2);   
    // add element

    return;
}

template<class T>
T CircularArray<T>::pop_front()
{  
    //cout << __PRETTY_FUNCTION__ << " ";
    if (array == nullptr || this->is_empty())
    {
        cerr << "pop_front() method doesn't work because structure is empty\n";
        return T{};
    }
    T rt_value = array[front];
    front = next(front);
    size_--;
    // estrategia para liberar espacios inutilizados
    //cout << " (" << size_ << ", " << capacity << ") -> ";
    if (size_ < (capacity/2))
        this->resize(capacity/2);
    
    return rt_value;
}

template<class T>
T CircularArray<T>::pop_back()
{
    //cout << __PRETTY_FUNCTION__ << " ";
    if (array == nullptr || this->is_empty())
    {
        cerr << "pop_back() method doesn't work because structure is empty\n";
        return T{};
    }
    T rt_value = array[back];
    back = prev(back);
    size_--;
    //cout << " (" << size_ << ", " << capacity << ") -> ";
    // estrategia para liberar espacios inutilizados
    if (size_ < (capacity/2))
        this->resize(capacity/2);
    
    return rt_value;
}

template<class T>
bool CircularArray<T>::is_full()
{
    return size_ == capacity;
}

template<class T>
bool CircularArray<T>::is_empty()
{
    //cout << " (" <<  size_ << ") ";
    return size_ == 0;
}

template<class T>
int CircularArray<T>::size()
{
    return size_;
}

template<class T>
void CircularArray<T>::resize(int new_capacity)
{
    cout << __PRETTY_FUNCTION__ << " " << new_capacity << " -> ";
    //cout << "resize\t " << new_capacity << "\t";
    //printArray(array, capacity); 
    //cout << "f: " << front << " b: " << back << endl;

    T* new_array = new T[new_capacity];
    int traverse = front;
    int i = traverse % new_capacity, aux_sz = 0;
    
    this->front = i;
    // copy numbers in new array
    while (aux_sz < min(new_capacity, capacity))
    {
        new_array[i] = array[traverse];
        i = (i + 1) % new_capacity;
        traverse = next(traverse);
        aux_sz++;
    }
    delete[] array;

    this->capacity = new_capacity;
    this->back = prev(i);
    this->array = new_array;

    //printArray(array, capacity);
    //cout << "f: " << front << " b: " << back << endl;

    return;
}

template<class T>
void CircularArray<T>::clear()
{
    delete[] array;
    capacity = size_ = 0;
    front = back = -1;
}

template<class T>
T& CircularArray<T>::operator[](int index)
{
    return array[index];
}

template<class T>
void CircularArray<T>::sort()
{
    // store values of array in auxiliar array -> O(n)
    T* aux_array = new T[size_];
    int traverse = front, i = 0; 
    while (traverse != back && i < size_)
    {
        aux_array[i] = array[traverse];
        traverse = next(traverse); i++;
    }
    aux_array[i] = array[traverse];

    // sort values in auxiliar array -> O(n logn)
    Introsort(aux_array, aux_array, aux_array + size_ - 1);

    // copy values from auxiliar array to array member attribute -> O(n)
    traverse = front, i = 0;
    while (traverse != back && i < size_)
    {
        array[traverse] = aux_array[i];
        traverse = next(traverse); i++;
    }
    array[traverse] = aux_array[i];

    delete[] aux_array;     // release memory
    return;
}

template<class T>
bool CircularArray<T>::is_sorted()
{
    // store values of array in auxiliar array -> O(n)
    T* aux_array = new T[size_];
    int traverse = front, i = 0;
    while (traverse != back && i < size_)
    {
        aux_array[i] = array[traverse];
        traverse = next(traverse); i++;
    }
    aux_array[i] = array[traverse];

    // sort values of auxiliar_array -> O(n logn)
    Introsort(aux_array, aux_array, aux_array + size_ - 1);

    // compare arrays -> O(n)
    traverse = front, i = 0;
    while(traverse != back && i < size_)
    {
        if (aux_array[i] != array[traverse])
        {
            delete[] aux_array;     // release memory
            return false;
        }
        traverse = next(traverse);
        i++;
    }
    if (aux_array[i] != array[traverse])
    {
        delete[] aux_array;     // release memory
        return false;
    }

    delete[] aux_array;     // release memory
    return true;
}

template<class T>
void CircularArray<T>::reverse()
{
    int sfront = front, sback = back;
    T temp;
    while (sfront != sback)          
    {
        // swap elements of complementary indices
        temp = array[sback];
        array[sback] = array[sfront];
        array[sfront] = temp;
        
        // move indices
        sfront = this->next(sfront);
        sback = this->prev(sback);
    }
    return;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index <= 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    int traverse = front; string result = ""; 
    // iterate between front & back markers
    int control_size = 0;
    //cout << " (" <<  size_ << ") ";
    while(traverse != back && control_size < size_)
    {
        result += std::to_string((*this)[traverse]) + sep;
        traverse = this->next(traverse);
        control_size++;
    }
    if (size_ == 0)
        return result;
    result += std::to_string((*this)[traverse]) + sep;
    return result;       
}

#include <iostream>
#include "circulararray.h"
#include "tester.h"

using namespace std;

void test_1()
{
    CircularArray<int>* array = new CircularArray<int>(7);
    ASSERT(array->is_empty() == true, "The function is_empty is not working");
    array->push_back(6);
    array->push_back(3);
    array->push_back(7);
    array->push_back(8);
    array->push_back(1);
    ASSERT(array->is_empty() == false, "The function is_empty is not working");
    ASSERT(array->is_full() == false, "The function is_full is not working");
    array->pop_front();
    array->pop_back();
    array->push_front(10);
    array->push_front(2);
    array->push_front(15);
    array->push_front(4);
    ASSERT(array->to_string() == "4 15 2 10 3 7 8 ", "The function push_front is not working");
    ASSERT(array->is_full() == true, "The function is_full is not working");
    ASSERT(array->is_sorted() == false, "The function is_sorted is not working");
    array->sort();
    ASSERT(array->to_string() == "2 3 4 7 8 10 15 ", "The function sort is not working");
    array->reverse();
    ASSERT(array->to_string() == "15 10 8 7 4 3 2 ", "The function reverse is not working");   
    delete array;
}

void test_2()
{
    //cout << __PRETTY_FUNCTION__ << " ";
    CircularArray<long long>* carray = new CircularArray <long long>(1);
    string showArray;
    for (long long i = 0; i <= 10; i++)
    {
        if (i & 1)  // "i" is odd
            carray->push_back(i);
        else
            carray->push_front(i);
        cout << carray->to_string() << '\n';
    }
    
    //cout << "pushs: "<< carray->to_string() << '\n';

    int j = 0;
    while(!carray->is_empty()){
        if (j&1){
            //cout << "pop_front():  "; 
            carray->pop_front();
        } 
        else
        {
            //cout << "pop_back():   "; 
            carray->pop_back();
        } 
        cout << carray->to_string() << '\n';
        j++;
    }
    cout << "carray: " << carray->to_string() << '\n';
    
    return;
}

void test_3()
{
    return;
}

int main() {
    cout << "\n\tTEST 1\n";
    test_1();

    cout << "\n\tTEST 2\n";
    test_2();

    cout << "\n\tTEST 3\n";
    return 0;
}
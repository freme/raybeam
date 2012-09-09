// test_dynarray.cc

#include "dynarray.h"
#include <iostream>

template <class T> bool status(DynArray<T>* array) {

    if (array->empty()) std::cout << "array(" << array->size() \
        << ") is empty" << std::endl;
    else std::cout << "array(" << array->size() \
        << ") has " << array->length() \
        << " elements" << std::endl;

    return true;
}

int main() {
    DynArray<int>* a = new DynArray<int>;
    DynArray<int>* b = new DynArray<int>(8);

    status(a);
    a->append(1);
    status(a);
    a->append(2);
    status(a);
    a->append(3);
    status(a);
    a->append(4);
    status(a);
    a->append(5);
    status(a);
    a->truncate();
    status(a);
    
    std::cout << "content of array:" << std::endl;
    for (int i = 0; i < a->length(); i++) std::cout << (*a)[i] << " "; 
    std::cout << std::endl;

    a->clear();
    b->clear();

    return 0;
}


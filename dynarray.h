// dynarray.h

#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_ 1

// doubles array size if full, use truncate() to manually free empty space
// add items via append()

template <class T> class DynArray {
    public:
        DynArray();
        DynArray(int);
        ~DynArray();

        bool append(T item); //adds to the end of array
        bool truncate();     //free empty cells
        void clear() {nData = 0; }
        int length() const { return nData; }
        int size() const { return arraySize; }
        bool empty() const { return nData == 0; }
        const T& operator[](int i) const { return data[i]; }
        T& operator[](int i) { return data[i]; }

        T* data;
        int nData;
        int arraySize;
};

template <class T> DynArray<T>::DynArray() {
    nData = 0;
    arraySize = 4;
    data = new T[arraySize];
}

template <class T> DynArray<T>::DynArray(int a) {
    nData = 0;
    arraySize = a;
    data = new T[arraySize];
}

template <class T> DynArray<T>::~DynArray() {
    nData = 0;
    delete [] data;
}

template <class T> bool DynArray<T>::truncate() {
    if (nData != arraySize) {
        T* tmp = data;
        arraySize = nData;

        if (!(data = new T[arraySize])) return false;

        for (int i = 0; i < nData; i++) data[i] = tmp[i]; //deep copy
        delete [] tmp;
    }
    return true;
}

template <class T> bool DynArray<T>::append(T item) {
    // double array if no more space available
    if (nData == arraySize) {
        arraySize *= 2;
        T* tmp = data;
        
        if (!(data = new T[arraySize])) return false;

        for (int i = 0; i < nData; i++) data[i] = tmp[i];
        delete [] tmp;
    }
    data[nData++] = item;
    return true;
}

#endif // _DYN_ARRAY_H_





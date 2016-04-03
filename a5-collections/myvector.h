#ifndef MYVECTOR_H
#define MYVECTOR_H

template <typename T>
class MyVector{
    private:
        T *ptrArray;                // pointer to the array
        int capacity;               // the capacity of the array
        int countElem;              // the number of elements
        void checkEmpty(std::string metod) const;
        bool checkEqual(const MyVector& objRef) const; //compares two vectors for equality
        void checkIndex(int index) const;
        void freeCapacity();
        void objCopy(const MyVector& objRef);
    public:
        MyVector(int size = 0);
        MyVector(const MyVector& objRef);       // the copy constructor
        ~MyVector();
        void push_back(const T& value);         // add an element to the end
        void insert(int index, const T& value); // insert an element in position index
        int getCapacity() const;
        bool empty() const;
        int size() const;
        T& operator [](int index);
        T& at(int index);
        T& back() const;                        // return the value of back element
        T& front() const;                       // return the value of front element
        MyVector& operator =(const MyVector& objRef);
        bool operator ==(const MyVector& objRef) const;
        bool operator !=(const MyVector& objRef) const;
        void show() const;
        void remove(int index);                 // remove an element from position index
        void pop_back();                        // remove the back element
        void clear();                           // remove all elements
};

// constructor
template <typename T>
MyVector<T>::MyVector(int size){
    capacity = countElem = size;
    ptrArray = size == 0 ? NULL : new T[capacity];
}

// copy constructor
template <typename T>
MyVector<T>::MyVector(const MyVector& objRef){
    objCopy(objRef);
}

// destructor
template <typename T>
MyVector<T>::~MyVector(){
    delete [] ptrArray;
}

// overload operator: =
template <typename T>
MyVector<T> & MyVector<T>::operator =(const MyVector& objRef){
    if (this != &objRef){
        delete[] ptrArray;
        objCopy(objRef);
    }
    return *this;
}

// overload operator: ==
template <typename T>
bool MyVector<T>::operator ==(const MyVector& objRef) const{
    return checkEqual(objRef);
}

// overload operator: !=
template <typename T>
bool MyVector<T>::operator !=(const MyVector& objRef) const{
    return !checkEqual(objRef);
}
/*
 * The method compares two vectors for equality
*/
template <typename T>
bool MyVector<T>::checkEqual(const MyVector<T>& objRef) const{
    if (size() != objRef.size()){
        return false;
    }
    for (int i = 0; i < countElem; i++){
        if (ptrArray[i] != objRef.ptrArray[i]){
            return false;
        }
    }
    return true;
}
/*
 * The method makes it possible to pass or return vectors by value
 * and assign from one vector to another
*/
template <typename T>
void MyVector<T>::objCopy(const MyVector& objRef){
    countElem = capacity = objRef.countElem;
    ptrArray = (capacity == 0) ? NULL : new T[capacity];
    for (int i = 0; i < countElem; i++){
        ptrArray[i] = objRef.ptrArray[i];
    }
}
/*
 * The method adds an element to the vector end
*/
template <typename T>
void MyVector<T>::push_back(const T& value){
    insert(countElem, value);
}
/*
 * The method inserts the element at position index, shifting elements to the right
 * and expanding the capacity if needed
*/
template <typename T>
void MyVector<T>::insert(int index, const T& value){
    try {
        if ((index < 0) || (index > countElem))
            throw std::string("ERROR! Vector index out of range!");
    }
    catch(std::string &ex){
        std::cout << ex;
        exit(0);
    }
    if (countElem == capacity){
        T *array = ptrArray;                //copy the pointer to the array
        capacity = capacity == 0 ? 1 : capacity * 2;
        ptrArray = new T[capacity];         //create an array with more capacity
        for (int i = 0; i < countElem; i++){
            ptrArray[i] = array[i];         //copy elements from old array
        }
        delete[] array;                     //delete the old array
    }
    for (int i = countElem; i > index; i--){
        ptrArray[i] = ptrArray[i - 1];      //shift the elements one position to the right
    }
    ptrArray[index] = value;                //put the element in the vector
    countElem++;
}
/*
 * The method returns the value of back element from this vector
*/
template <typename T>
T& MyVector<T>::back() const{
    checkEmpty("back");
    return ptrArray[countElem - 1];
}
/*
 * The method returns the value of front element from this vector
*/
template <typename T>
T& MyVector<T>::front() const{
    checkEmpty("front");
    return ptrArray[0];
}

// overload operator: []
template <typename T>
T& MyVector<T>::operator [](int index){
    checkIndex(index);
    return ptrArray[index];
}
/*
 * The method of access specified element with index checking
*/
template <typename T>
T& MyVector<T>::at(int index){
    checkIndex(index);
    return ptrArray[index];
}
/*
 * The method removes the back element from vector
*/
template <typename T>
void MyVector<T>::pop_back(){
    checkEmpty("pop_back");
    countElem--;
    freeCapacity();
}
/*
 * The method removes the element from position index,
 * shifting elements to the left
*/
template <typename T>
void MyVector<T>::remove(int index){
    checkIndex(index);
    for (int i = index; i < countElem - 1; i++){
        ptrArray[i] = ptrArray[i + 1];
    }
    countElem--;
    freeCapacity();    //free memory
}
/*
 * Тhe method determines the vector size
 * @return Тhe number of elements in the vector
*/
template <typename T>
int MyVector<T>::size() const{
    return countElem;
}
/*
 * The method returns the capacity of container that is allocated memory now
*/
template <typename T>
int MyVector<T>::getCapacity() const{
    return capacity;
}
/*
 * The method removes all elements from the container
*/
template <typename T>
void MyVector<T>::clear(){
    delete [] ptrArray;
    capacity = countElem = 0;
    ptrArray = NULL;
}
/*
 * The method displays capacity, size and the vector elements
*/
template <typename T>
void MyVector<T>::show() const{
    std::cout << "capacity: " << getCapacity() << std::endl;
    std::cout << "size: " << size() << std::endl;
    for (int i = 0; i < countElem; i++){
        std::cout << "[" << i << "]=" << ptrArray[i] << std::endl;
    }
}
/*
 * The method returns true if the vector is empty
*/
template <typename T>
bool MyVector<T>::empty() const{
    return size() == 0;
}
/*
 * This method reduces the capacity of the array, copies the old elements into the new array,
 * and then frees the old.
*/
template <typename T>
void MyVector<T>::freeCapacity(){
    if (countElem < capacity/2){
        T *array = ptrArray;                //copy the pointer to the array
        capacity /= 2;
        ptrArray = new T[capacity];         //create an array with less capacity
        for (int i = 0; i < countElem; i++){
            ptrArray[i] = array[i];         //copy elements from old array
        }
        delete[] array;                     //delete the old array
    }
}
/*
 * The method displays an error if the vector is empty
 * @param metod The name of the method that called this method
*/
template <typename T>
void MyVector<T>::checkEmpty(std::string metod) const{
    try {
        if (empty())
            throw std::string("ERROR! Attempting to " + metod + "() an empty vector!");
    }
    catch(std::string &ex){
        std::cout << ex;
        exit(0);
    }
}
/*
 * The method displays an error if the vector index out of range
 * @param metod The name of the method that called this method
*/
template <typename T>
void MyVector<T>::checkIndex(int index) const{
    try {
        if ((index < 0) || (index >= countElem))
            throw std::string("ERROR! Vector index out of range!");
    }
    catch(std::string &ex){
        std::cout << ex;
        exit(0);
    }
}
#endif // MYVECTOR_H

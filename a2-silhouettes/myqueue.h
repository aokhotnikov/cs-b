#ifndef MYQUEUE_H
#define MYQUEUE_H

template <typename T>
class MyQueue{
    private:
        T *ptrArray;            // pointer to the array
        unsigned int capacity;  // the capacity of the array
        unsigned int countElem; // the number of elements
        unsigned int frontEl;   // pos front element
        unsigned int backEl;    // pos back element
        void extendCapacity();
        void checkEmpty(std::string metod) const;
    public:
        MyQueue();
        ~MyQueue();
        unsigned int size() const;
        void push(const T&);    // add the element
        bool empty() const;
        void show() const;
        T& front() const;       // return the value of front element
        T& back() const;        // return the value of back element
        void pop();             // remove the front element
};

// constructor
template <typename T>
MyQueue<T>::MyQueue(){
    capacity = countElem = 0;
    ptrArray = NULL;
}

// destructor
template <typename T>
MyQueue<T>::~MyQueue(){
    delete [] ptrArray;
}
/*
 * The method adds an element to the queue
*/
template <typename T>
void MyQueue<T>::push(const T& value){
    if (countElem == capacity){
        extendCapacity();
    }
    countElem++;

    if (countElem == 1)
        frontEl = backEl = 0;
    else{
        backEl = (backEl + 1 == capacity) ? 0 : backEl + 1;
    }

    ptrArray[backEl] = value;                    //put the element in the queue
}
/*
 * The method removes the top element from queue
*/
template <typename T>
void MyQueue<T>::pop(){
    //checkEmpty("pop"); // for debag
    frontEl = (frontEl + 1 == capacity) ? 0 : frontEl + 1;
    countElem--;
}
/*
 * The method returns the value of back element from this queue
*/
template <typename T>
T& MyQueue<T>::back() const{
    //checkEmpty("back"); // for debag
    return ptrArray[backEl];
}
/*
 * The method returns the value of front element from this queue
*/
template <typename T>
T& MyQueue<T>::front() const{
    //checkEmpty("front"); // for debag
    return ptrArray[frontEl];
}
/*
 * Тhe method determines the queue size
 * @return Тhe number of elements in the stack
*/
template <typename T>
unsigned int MyQueue<T>::size() const{
    return countElem;
}
/*
 * The method returns true if the queue is empty
*/
template <typename T>
bool MyQueue<T>::empty() const{
    return size() == 0;
}
/*
 * The method displays the queue elements
*/
template <typename T>
void MyQueue<T>::show() const{
    std::cout << "capacity: " << capacity << std::endl;
    std::cout << "size: " << size() << std::endl;
    std::cout << "front: [" << frontEl << "]=" << front() << std::endl;
    std::cout << "back: [" << backEl << "]=" << back() << std::endl;
    unsigned int i = frontEl;
    for (unsigned int j = 0; j != countElem; j++){
        std::cout << "[" << i << "]=" << ptrArray[i] << std::endl;
        i++;
        if (i == capacity) i = 0;
    }
}
/*
 * This method extends the capacity of the array, copies the old elements into the new array,
 * and then frees the old.
*/
template <typename T>
void MyQueue<T>::extendCapacity(){
    T *array = ptrArray;                        //copy the pointer to the array
    capacity = capacity == 0 ? 1 : capacity * 2;
    ptrArray = new T[capacity];                 //create an array with more capacity
    for (unsigned int i = 0; i < countElem; i++){
        ptrArray[i] = array[frontEl];           //copy elements from old array
        frontEl++;
        if (frontEl == countElem){
            frontEl = 0;
        }
    }
    if (countElem > 0){
        backEl = countElem - 1;
        frontEl = 0;
    }
    delete[] array;                             //delete the old array
}
/*
 * The method displays an error if the queue is empty
 * @param metod The name of the method that called this method
*/
template <typename T>
void MyQueue<T>::checkEmpty(std::string metod) const{
    try{
        if (empty())
            throw std::string("ERROR! Attempting to " + metod + "() an empty queue!");
    }
    catch(std::string &ex){
        std::cout << ex;
        exit(0);
    }
}

#endif // MyQueue_H

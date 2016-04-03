#ifndef MYSTACK_H
#define MYSTACK_H

template <typename T>
class MyStack{
    private:
        T *ptrArray;            // pointer to the array
        int capacity;           // the capacity of the array
        int countElem;          // the number of elements
        void freeCapacity();
        void checkEmpty(std::string metod) const;
    public:
        MyStack();
        ~MyStack();
        void push(const T&);    // add the element
        bool empty() const;
        void show() const;
        int size() const;
        T& top() const;         // return the value of top element
        void pop();             // remove the top element
};

// constructor
template <typename T>
MyStack<T>::MyStack(){
    capacity = countElem = 0;
    ptrArray = NULL;
}

// destructor
template <typename T>
MyStack<T>::~MyStack(){
    delete [] ptrArray;
}
/*
 * The method adds an element to the stack
*/
template <typename T>
void MyStack<T>::push(const T& value){
    if (countElem == capacity){
        T *array = ptrArray;                        //copy the pointer to the array
        capacity = capacity == 0 ? 1 : capacity * 2;
        ptrArray = new T[capacity];                 //create an array with more capacity
        for (int i = 0; i < countElem; i++){
            ptrArray[i] = array[i];                 //copy elements from old array
        }
        delete[] array;                             //delete the old array
    }
    ptrArray[countElem] = value;                    //put the element in the stack
    countElem++;
}
/*
 * The method removes the top element from stack
*/
template <typename T>
void MyStack<T>::pop(){
    checkEmpty("pop");
    countElem--;
    freeCapacity();
}
/*
 * The method returns the value of top element from this stack
*/
template <typename T>
T& MyStack<T>::top() const{
    checkEmpty("top");
    return ptrArray[countElem - 1];
}
/*
 * Тhe method determines the stack size
 * @return Тhe number of elements in the stack
*/
template <typename T>
int MyStack<T>::size() const{
    return countElem;
}
/*
 * The method returns true if the stack is empty
*/
template <typename T>
bool MyStack<T>::empty() const{
    return size() == 0;
}
/*
 * The method displays the stack elements
*/
template <typename T>
void MyStack<T>::show() const{
    std::cout << "capacity: " << capacity << std::endl;
    std::cout << "size: " << size() << std::endl;
    for (int i = 0; i < countElem; i++){
        std::cout << "[" << i << "]=" << ptrArray[i] << std::endl;
    }
}
/*
 * This method reduces the capacity of the array, copies the old elements into the new array,
 * and then frees the old.
*/
template <typename T>
void MyStack<T>::freeCapacity(){
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
 * The method displays an error if the stack is empty
 * @param metod The name of the method that called this method
*/
template <typename T>
void MyStack<T>::checkEmpty(std::string metod) const{
    try{
        if (empty())
            throw std::string("ERROR! Attempting to " + metod + "() an empty stack!");
    }
    catch(std::string &ex){
        std::cout << ex;
        exit(0);
    }
}

#endif // MYSTACK_H

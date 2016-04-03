#ifndef MYQUEUE2_H
#define MYQUEUE2_H

template <typename T>
class MyQueue{
    private:
        class Elem{
            public:
                T data;
                Elem *next;      // pointer to the next element
        };
        Elem *frontEl;           // pointer to the front element
        Elem *backEl;            // pointer to the back element
        int countElem;           // the number of elements
        void checkEmpty(std::string metod) const;
        void showElements(const Elem *el) const;
    public:
        MyQueue();
        ~MyQueue();
        void push(const T&);     // add the element
        bool empty() const;
        void show() const;
        int size() const;
        T& front();              // return the value of front element
        T& back();               // return the value of back element
        void pop();              // remove the front element
};

// constructor
template <typename T>
MyQueue<T>::MyQueue(){
    frontEl = backEl = NULL;
    countElem = 0;
}

// destructor
template <typename T>
MyQueue<T>::~MyQueue(){
    while(countElem !=0){
        pop();
    }
    frontEl = backEl = NULL;
}
/*
 * The method adds an element to the end of the queue
*/
template <typename T>
void MyQueue<T>::push(const T& data){
    Elem *newElem = new Elem();
    newElem->data = data;
    newElem->next = NULL;
    //add an element to the tail of the queue
    empty() ? frontEl = newElem : backEl->next = newElem;

    backEl = newElem;
    countElem++;
}
/*
 * The method removes the front element of the queue
*/
template <typename T>
void MyQueue<T>::pop(){
    checkEmpty("pop");
    Elem *newElem = frontEl;
    frontEl = newElem->next;
    delete newElem;
    countElem--;
}
/*
 * The method returns the value of front element from this queue
*/
template <typename T>
T& MyQueue<T>::front(){
    checkEmpty("front");
    return frontEl->data;
}
/*
 * The method returns the value of back element from this queue
*/
template <typename T>
T& MyQueue<T>::back(){
    checkEmpty("back");
    return backEl->data;
}
/*
 * Тhe method determines the queue size
 * @return Тhe number of elements in the queue
*/
template <typename T>
int MyQueue<T>::size() const{
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
 * The method calls a private method for displaying elements
*/
template <typename T>
void MyQueue<T>::show() const{
    showElements(frontEl);
}
/*
 * The method using recursion, displays the elements
*/
template <typename T>
void MyQueue<T>::showElements(const Elem *el) const{
    std::cout << el->data << std::endl;
    if (el->next != NULL){
        showElements(el->next);
    }
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

#endif // MYQUEUE2_H

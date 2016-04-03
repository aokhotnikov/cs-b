#ifndef MYLIST_H
#define MYLIST_H

template <typename T>
class MyList{
    private:
        class Elem{
            public:
                T data;
                Elem *next;              // pointer to the next element
                Elem *prev;              // pointer to the previous element
                Elem() : next(NULL), prev(NULL){}
        };
        Elem *frontEl;                   // pointer to the front element
        Elem *backEl;                    // pointer to the back element
        int countElem;                   // the number of elements
        void checkEmpty(std::string metod) const;
        void showElements(const Elem *el) const;
        void checkIndex(int index) const;
        Elem *getElem(int index) const;
    public:
        MyList();
        ~MyList();
        void insert(int index, const T&);// insert an element in position index
        T& getElemData(int index);       // get the element value
        void push_front(const T&);       // add an element to the list front
        void push_back(const T&);        // add an element to the list back
        bool empty() const;
        void show() const;
        int size() const;
        void pop_front();                // remove the front element
        void pop_back();                 // remove the back element
        void clear();                    // remove all elements
        void sort();                     // sort elements
        T& front();                      // return the value of front element
        T& back();                       // return the value of back element

        class iterator{
        private:
            Elem *el;                    // current element
            int index;                   // current element index
        public:
            iterator(Elem *el = NULL, int index = 0);
            iterator(const iterator& it);//copy constructor
            iterator& operator ++();     //prefix increment (++x)
            iterator operator ++(int);   //postfix increment (x++)
            iterator& operator --();     //prefix decrement (--x)
            iterator operator --(int);   //postfix decrement (x--)
            bool operator ==(const iterator& it);
            bool operator !=(const iterator& it);
            bool operator <(const iterator& it);
            bool operator <=(const iterator& it);
            bool operator >(const iterator& it);
            bool operator >=(const iterator& it);
            iterator operator +(const int j);
            iterator operator -(const int j);
            T& operator *();
            T* operator ->();
            Elem* getEl() const;
            int getIndex() const;
        };

        iterator begin() const;
        iterator end() const;
        void insert(iterator &it, const T& data); // insert an element in position iterator
        void sort(iterator &begin, iterator &end);// sort elements
};

//constructor
template <typename T>
MyList<T>::MyList(){
    frontEl = backEl = NULL;
    countElem = 0;
}

//destructor
template <typename T>
MyList<T>::~MyList(){
    clear();
}
/*
 * The method removes all elements from the container
*/
template <typename T>
void MyList<T>::clear(){
    while(countElem !=0) {
        Elem *newElem = backEl;
        if (newElem->prev != NULL)
            backEl = newElem->prev;
        if (backEl->next != NULL)
            backEl->next = NULL;
        delete newElem;
        countElem--;
    }
    frontEl = backEl = NULL;
}
/*
 * The method adds an element to the list end
*/
template <typename T>
void MyList<T>::push_back(const T& data){
    Elem *newElem = new Elem();
    newElem->data = data;
    if (frontEl == NULL)
        frontEl = newElem;
    else{
        backEl->next = newElem;//reference to newly created element
        newElem->prev = backEl;//reference to previous element
    }
    backEl = newElem;
    countElem++;
}
/*
 * The method adds an element to the list begin
*/
template <typename T>
void MyList<T>::push_front(const T& data){
    Elem *newElem = new Elem();
    newElem->data = data;
    if (backEl == NULL)
        backEl = newElem;
    else{
        frontEl->prev = newElem;//reference to newly created element
        newElem->next = frontEl;//reference to next element
    }
    frontEl = newElem;
    countElem++;
}
/*
 * The method inserts an element in position index
 *
 * @param index The position at which to insert the value
 * @param data The value to insert
*/
template <typename T>
void MyList<T>::insert(int index, const T& data){
    checkIndex(index);
    if (index == 0)
        push_front(data);
    else if (index == size())
        push_back(data);
    else {
        Elem *newElem = new Elem();
        newElem->data = data;

        Elem *indexEl = getElem(index);

        newElem->prev = indexEl->prev;
        newElem->next = indexEl;
        indexEl->prev->next = newElem;
        indexEl->prev = newElem;
        countElem++;
    }
}
/*
 * The method inserts an element in position iterator
 *
 * @param it The position of the iterator at which to insert the value
 * @param data The value to insert
*/
template <typename T>
void MyList<T>::insert(iterator &it, const T& data){
    int index = it.getIndex();
    checkIndex(index);
    if (index == 0)
        push_front(data);
    else if (index == size())
        push_back(data);
    else {
        Elem *newElem = new Elem();
        newElem->data = data;

        Elem *indexEl = it.getEl();

        newElem->prev = indexEl->prev;
        newElem->next = indexEl;
        indexEl->prev->next = newElem;
        indexEl->prev = newElem;
        countElem++;
    }
}
/*
 * The method removes the front element of the list
*/
template <typename T>
void MyList<T>::pop_front(){
    checkEmpty("pop_front");
    Elem *newElem = frontEl;
    if (countElem == 1)
        frontEl = backEl = NULL;
    else{
        frontEl = newElem->next;
        if (frontEl->prev != NULL)
            frontEl->prev = NULL;
    }
    delete newElem;
    countElem--;
}
/*
 * The method removes the back element of the list
*/
template <typename T>
void MyList<T>::pop_back(){
    checkEmpty("pop_back");
    Elem *newElem = backEl;
    if (countElem == 1)
        frontEl = backEl = NULL;
    else{
        backEl = newElem->prev;
        if (backEl->next != NULL)
            backEl->next = NULL;
    }
    delete newElem;
    countElem--;
}
/*
 * The method sorts elements by the bidirectional selection sort algorithm.
 * On the average, algorithm has O(n*n/2) complexity, making selection sort
 * suitable for sorting small data volumes.
*/
template <typename T>
void MyList<T>::sort(){
    for (auto it = begin(); it <= end(); ++it){
        auto min = it;
        auto max = end() - it.getIndex();
        auto itEnd = max;
        for (auto it2 = it; it2 <= itEnd; ++it2){
            if (*min > *it2)
                min = it2;
            if (*max < *it2)
                max = it2;
        }
        if (max != min){
            T data = *it;
            if (data == *max) max = min;
            *it = *min;
            *min = data;
            data = *itEnd;
            *itEnd = *max;
            *max = data;
        }
    }
}
/*
 * The method sorts elements by the quicksort algorithm. On the average,
 * algorithm has O(n log n) complexity, making quicksort suitable for
 * sorting big data volumes. The divide-and-conquer strategy is used in quicksort.
 *
 * @param first The position of the iterator which will begin to sort the elements.
 *              It's not necessary that the element was in the beginning of the list
 * @param last  The latest position of the iterator will be sorting the elements.
 *              It's not necessary that the element was at the end of the list
*/
template <typename T>
void MyList<T>::sort(iterator &first, iterator &last){
    auto left = first;
    auto right = last;
    auto middle = first;
    while(middle.getIndex() < last.getIndex()/2){
        middle++;
    }
    while (left.getIndex() < right.getIndex()){
        while (*left < *middle){
            left++;
        }
        while (*right > *middle){
            right--;
        }
        if (left.getIndex() <= right.getIndex()){
            T dump = *left;
            *left = *right;
            *right = dump;
            right--;
            left++;
        }
    }
    if(first.getIndex() < right.getIndex()){
        sort(first, right);
    }
    if(left.getIndex() < last.getIndex()){
        sort(left, last);
    }
}
/*
 * The method returns the value of the element
 * @param index The element position
*/
template <typename T>
T& MyList<T>::getElemData(int index){
    Elem *el = getElem(index);
    return el->data;
}
/*
 * The method returns a list element
 * @param index The element position
*/
template <typename T>
typename MyList<T>::Elem *MyList<T>::getElem(int index) const{
    checkIndex(index);
    if (index == 0)
        return frontEl;
    if (index == size())
        return backEl;
    Elem *indexEl = frontEl;
    for (int i = 0; i < index; i++){
        indexEl = indexEl->next;
    }
    return indexEl;
}
/*
 * The method returns the value of front element from this list
*/
template <typename T>
T& MyList<T>::front(){
    checkEmpty("front");
    return frontEl->data;
}
/*
 * The method returns the value of back element from this list
*/
template <typename T>
T& MyList<T>::back(){
    checkEmpty("back");
    return backEl->data;
}
/*
 * Тhe method determines the list size
 * @return Тhe number of elements in the list
*/
template <typename T>
int MyList<T>::size() const{
    return countElem;
}
/*
 * The method returns true if the list is empty
*/
template <typename T>
bool MyList<T>::empty() const{
    return size() == 0;
}
/*
 * The method calls a private method for displaying elements
*/
template <typename T>
void MyList<T>::show() const{
    showElements(frontEl);
}
/*
 * The method using recursion, displays the elements
*/
template <typename T>
void MyList<T>::showElements(const Elem *el) const{
    std::cout << el->data << std::endl;
    if (el->next != NULL){
        showElements(el->next);
    }
}
/*
 * The method displays an error if the list is empty
 * @param metod The name of the method that called this method
*/
template <typename T>
void MyList<T>::checkEmpty(std::string metod) const{
    try {
        if (empty())
            throw std::string("ERROR! Attempting to " + metod + "() an empty list!");
    }
    catch(std::string &ex){
        std::cout << ex;
        exit(0);
    }
}
/*
 * The method displays an error if the list index out of range
 * @param metod The name of the method that called this method
*/
template <typename T>
void MyList<T>::checkIndex(int index) const{
    try {
        if ((index < 0) || (index > countElem))
            throw std::string("ERROR! List index out of range!");
    }
    catch(std::string &ex){
        std::cout << ex;
        exit(0);
    }
}
/*
 * The method returns an iterator to the first element
*/
template <typename T>
typename MyList<T>::iterator MyList<T>::begin() const{
    return iterator(this->getElem(0), 0);
}
/*
 * The method returns an iterator to the last element
*/
template <typename T>
typename MyList<T>::iterator MyList<T>::end() const{
    return iterator(this->getElem(countElem), countElem - 1);
}

//---------------------------------class Iterator-----------------------------

// The constructor for class "iterator"
template <typename T>
MyList<T>::iterator::iterator(Elem *el, int index){
    this->el = el;
    this->index = index;
}

// The copy constructor for class "iterator"
template <typename T>
MyList<T>::iterator::iterator(const iterator& it){
    this->el = it.el;
    this->index = it.index;
}

// Overloaded "operator ++x" for class "iterator"
template <typename T>
typename MyList<T>::iterator& MyList<T>::iterator::operator ++(){
    index++;
    el = el->next;
    return *this;
}

// Overloaded "operator x++" for class "iterator"
template <typename T>
typename MyList<T>::iterator MyList<T>::iterator::operator ++(int){
    iterator itCopy(*this);
    operator++();
    return itCopy;
}

// Overloaded "operator --x" for class "iterator"
template <typename T>
typename MyList<T>::iterator& MyList<T>::iterator::operator --(){
    index--;
    el = el->prev;
    return *this;
}

// Overloaded "operator x--" for class "iterator"
template <typename T>
typename MyList<T>::iterator MyList<T>::iterator::operator --(int){
    iterator itCopy(*this);
    operator--();
    return itCopy;
}

// Overloaded "operator ==" for class "iterator"
template <typename T>
bool MyList<T>::iterator::operator ==(const iterator& it){
    return el == it.el && index == it.index;
}

// Overloaded "operator !=" for class "iterator"
template <typename T>
bool MyList<T>::iterator::operator !=(const iterator& it){
    return !(*this == it);
}

// Overloaded "operator <" for class "iterator"
template <typename T>
bool MyList<T>::iterator::operator <(const iterator& it){
    return index < it.index;
}

// Overloaded "operator <=" for class "iterator"
template <typename T>
bool MyList<T>::iterator::operator <=(const iterator& it){
    return index <= it.index;
}

// Overloaded "operator >" for class "iterator"
template <typename T>
bool MyList<T>::iterator::operator >(const iterator& it){
    return index > it.index;
}

// Overloaded "operator >=" for class "iterator"
template <typename T>
bool MyList<T>::iterator::operator >=(const iterator& it){
    return index >= it.index;
}

// Overloaded "operator +" for class "iterator"
template <typename T>
typename MyList<T>::iterator MyList<T>::iterator::operator +(const int j){
    iterator itCopy(*this);
    for (int i = 0; i < j; i++){
        ++itCopy;
    }
    return itCopy;
}

// Overloaded "operator -" for class "iterator"
template <typename T>
typename MyList<T>::iterator MyList<T>::iterator::operator -(const int j){
    iterator itCopy(*this);
    for (int i = 0; i < j; i++){
        --itCopy;
    }
    return itCopy;
}

// Overloaded "operator *" for class "iterator"
template <typename T>
T& MyList<T>::iterator::operator *(){
    return el->data;
}

// Overloaded "operator ->" for class "iterator"
template <typename T>
T* MyList<T>::iterator::operator ->(){
    return &el->data;
}

// The method returns a pointer to the element
template <typename T>
typename MyList<T>::Elem* MyList<T>::iterator::getEl() const{
    return el;
}

// The method returns the element's position in the list
template <typename T>
int MyList<T>::iterator::getIndex() const{
    return index;
}

#endif // MYLIST_H

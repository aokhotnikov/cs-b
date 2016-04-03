#ifndef MYUNORDERED_MAP_H
#define MYUNORDERED_MAP_H

template <typename K, typename V>
class MyUnordered_map{
    private:
        const double LOADFACTOR = 0.75; // The load factor of the container
        class Cell{
            public:
                K key;
                V value;
                Cell *next;
                Cell() : next(nullptr){}
        };
        Cell **ptrArray;                // pointer to an array of pointers
        int numBuckets;                 // the number of the buckets(capacity)
        int numCells;                   // the number of cells
        int findBucket(K key);
        Cell *addCell(K key);
        Cell *findCell(K key);
        Cell *createCell(K key);
        bool checkSize() const;
        void expandNumBuckets();
    public:
        MyUnordered_map(int size = 16);
        ~MyUnordered_map();
        void add(K key, V value);
        V& at(K key);
        V& operator [](K key);
        bool containsKey(K key);
        bool empty() const;
        void remove(K key);             // remove element
        void show() const;
        int size() const;
        void clear();                   // remove all elements

        class iterator{
        private:
            const MyUnordered_map* hMap; // pointer to the hashmap
            int index;                   // index of current bucket
            Cell* cp;                    // current cell in bucket
        public:
            iterator() : hMap(nullptr), cp(nullptr), index(0){}
            iterator(const MyUnordered_map *hm, int indexBucket); // for begin and end metods
            iterator& operator ++();     //prefix increment (++x)
            bool operator ==(const iterator& it);
            bool operator !=(const iterator& it);
            Cell* operator ->();         // for it->key or it->value
            Cell& operator *();          // for (*it).key or (*it).value
        };

        iterator begin() const;
        iterator end() const;
};

// The constructor for MyUnordered_map class
template <typename K, typename V>
MyUnordered_map<K,V>::MyUnordered_map(int size){
    numBuckets = size;
    numCells = 0;
    ptrArray = new Cell*[numBuckets];
    for (int i = 0; i < numBuckets; ++i){
        ptrArray[i] = nullptr;
    }
}

// The destructor for MyUnordered_map class
template <typename K, typename V>
MyUnordered_map<K,V>::~MyUnordered_map(){
    clear();
    delete [] ptrArray;
}
/*
 * The method returns a reference to the associated value of the
 * element with key "key" in the container. If the element is not
 * found then it is created
*/
template <typename K, typename V>
V& MyUnordered_map<K,V>::at(K key){
    Cell *cp = findCell(key);
    if (cp == nullptr){
        cp = addCell(key);
    }
    return cp->value;
}

// overload operator: []
template <typename K, typename V>
V& MyUnordered_map<K,V>::operator [](K key){
    return at(key);
}

// The method adds an element to the container
template <typename K, typename V>
void MyUnordered_map<K,V>::add(K key, V value){
    at(key) = value;
}
/*
 * When the container is filled to the limit, its size doubled
 * and redistribution elements. The method iterates through all
 * the elements of this array, recounts their indices (including
 * the new size) and redistributes the elements of the new array
*/
template <typename K, typename V>
void MyUnordered_map<K,V>::expandNumBuckets(){
        Cell **array = ptrArray; // copy the pointer to an array of pointers

        //expand capacity
        numBuckets *= 2;
        ptrArray = new Cell*[numBuckets];
        for (int i = 0; i < numBuckets; i++){
            ptrArray[i] = nullptr;
        }

        //copy the pointers to the elements
        for (int j = 0; j < numBuckets/2; j++){
            Cell *cp = array[j];
            while (cp != nullptr){
                Cell *cpNext = cp->next;     // copy the pointer to the
                                             // next element in Bucket
                cp->next = nullptr;
                int i = findBucket(cp->key); // new index in the ptrArray[]
                if (ptrArray[i] == nullptr)
                    ptrArray[i] = cp;
                else{                        // cell will be the parent
                    Cell *nextCell = ptrArray[i];
                    ptrArray[i] = cp;
                    cp->next = nextCell;
                }
                cp = cpNext;
            }
        }
        delete[] array;          // delete the old array
}
/*
 * The method creates a cell and returns a pointer to it
*/
template <typename K, typename V>
typename MyUnordered_map<K,V>::Cell *MyUnordered_map<K,V>::createCell(K key){
    Cell *newCell = new Cell();
    newCell->key = key;
    numCells++;

    return newCell;
}
/*
 * The method adds an element to the container. First, checks
 * the load factor at which the size of the hashmap is doubled.
 * Secondly, determines the position in the array where the element
 * will be placed. And if the bucket is empty, add an item to it.
 * If the bucket is full, add item at start of list.
*/
template <typename K, typename V>
typename MyUnordered_map<K,V>::Cell *MyUnordered_map<K,V>::addCell(K key){
    if (!checkSize()){
        expandNumBuckets();
    }

    int i = findBucket(key);
    if (ptrArray[i] == nullptr)
        ptrArray[i] = createCell(key);
    else{                             // cell will be the parent
        Cell *cp = ptrArray[i];
        ptrArray[i] = createCell(key);
        ptrArray[i]->next = cp;
    }

    return ptrArray[i];
}
/*
 * The method searches the element in the container by a key
 *
 * @param key The key element
 * @return A pointer to the cell containing the element
*/
template <typename K, typename V>
typename MyUnordered_map<K,V>::Cell *MyUnordered_map<K,V>::findCell(K key){
    int i = findBucket(key);
    Cell *cp = ptrArray[i];
    if (cp != nullptr){
        if (cp->key == key){
            return cp;
        }
        while (cp->next != nullptr){ // if cell is the parent
            cp = cp->next;
            if (cp->key == key)
                return cp;
        }
    }
    return nullptr;
}
/*
 * The method generates a hash based on the key and returns
 * the position in the array where the element will be placed
 *
 * @param key The key element
 * @return The position in the array
*/
template <typename K, typename V>
int MyUnordered_map<K,V>::findBucket(K key){
    std::hash<K> h;
    return h(key) & (numBuckets - 1); // or  h(key) % numBuckets
}
/*
 * Тhe method determines the hashmap size
 * @return Тhe number of elements in the hashmap
*/
template <typename K, typename V>
int MyUnordered_map<K,V>::size() const{
    return numCells;
}
/*
 * The method returns true if the hashmap is empty
*/
template <typename K, typename V>
bool MyUnordered_map<K,V>::empty() const{
    return size() == 0;
}
/*
 * The method compares the load factor of the container with
 * the container size. The default value of 0.75 is a good
 * compromise between access time and storage capacity
*/
template <typename K, typename V>
bool MyUnordered_map<K,V>::checkSize() const{
    return size() < numBuckets * LOADFACTOR;
}
/*
 * The method removes from the container single element
 * @param key The key of the element to be removed
*/
template <typename K, typename V>
void MyUnordered_map<K,V>::remove(K key){
    if(containsKey(key)){
        int i = findBucket(key);
        Cell *cp = ptrArray[i];

        if (cp->key == key)
            ptrArray[i] = (cp->next == nullptr) ? nullptr : cp->next;
        else{
            //search in bucket
            Cell *cpParent;
            while (cp->key != key){
                cpParent = cp;
                cp = cp->next;
            }
            cpParent->next = (cp->next == nullptr) ? nullptr : cp->next;
        }
        delete cp;
        numCells--;
    }
    else
        std::cout << "The key [" << key << "] is missing" << std::endl;
}
/*
 * The method returns "true", if there is an entry for a key in the container
*/
template <typename K, typename V>
bool MyUnordered_map<K,V>::containsKey(K key){
    return findCell(key) != nullptr;
}
/*
 * The method removes all elements from the container
*/
template <typename K, typename V>
void MyUnordered_map<K,V>::clear(){
    for (int i = 0; i < numBuckets; i++){
        if (ptrArray[i] != nullptr){
            Cell *cp = ptrArray[i];
            while (cp->next != nullptr){
                Cell *cpForDel = cp;
                cp = cp->next;
                delete cpForDel;
            }
            delete cp;
            ptrArray[i] = nullptr;
        }
    }
    numCells = 0;
}
/*
 * The method displays the unordered_map elements(for debag)
*/
template <typename K, typename V>
void MyUnordered_map<K,V>::show() const{
    std::cout << "numBuckets: " << numBuckets << std::endl;
    std::cout << "numCells: " << size() << std::endl;
    for (int i = 0; i < numBuckets; i++){
        if (ptrArray[i] != nullptr){
            std::cout << "[" << ptrArray[i]->key << "]=" << ptrArray[i]->value;
            Cell *cp = ptrArray[i];
            while (cp->next != nullptr){
                cp = cp->next;
                std::cout << "   [" << cp->key << "]=" << cp->value;
            }
        std::cout << std::endl;
        }else
            std::cout << "[]=" << std::endl;
    }
}
/*
 * The method returns an iterator to the first element
*/
template <typename K, typename V>
typename MyUnordered_map<K,V>::iterator MyUnordered_map<K,V>::begin() const{
    return iterator(this, 0);
}
/*
 * The method returns an iterator to the element following the last
*/
template <typename K, typename V>
typename MyUnordered_map<K,V>::iterator MyUnordered_map<K,V>::end() const{
    return iterator(this, this->numBuckets);
}

//-------------------------------class Iterator--------------------------------------
/*
 * The constructor for class "iterator" is used when
 * initializing the iterator the beginning and end
 *
 * @param hm The array of buckets(hashmap)
 * @param indexBucket A backet index in a hashmap
*/
template <typename K, typename V>
MyUnordered_map<K,V>::iterator::iterator(const MyUnordered_map *hm, int indexBucket){
    hMap = hm;
    if (indexBucket == 0){    //begin iterator
        index = 0;
        cp = hMap->ptrArray[index];
        while (cp == nullptr){//find next in ptrArray
            cp = hMap->ptrArray[++index];
        }
    }else{                    //end iterator
        index = indexBucket;
        cp = nullptr;
    }
}

// Overloaded "operator ++" for class "iterator" (increment (++x))
template <typename K, typename V>
typename MyUnordered_map<K,V>::iterator& MyUnordered_map<K,V>::iterator::operator ++(){
    if (cp->next != nullptr) // if child exist
        cp = cp->next;       // cp = child
    else {
        cp = nullptr;
        while ((cp == nullptr) && (++index < hMap->numBuckets)){
            cp = hMap->ptrArray[index];
        }
    }
    return *this;
}

// Overloaded "operator ==" for class "iterator"
template <typename K, typename V>
bool MyUnordered_map<K,V>::iterator::operator ==(const iterator& it){
    return (this->index == it.index && this->cp == it.cp);
}

// Overloaded "operator !=" for class "iterator"
template <typename K, typename V>
bool MyUnordered_map<K,V>::iterator::operator !=(const iterator& it){
    return !(*this == it);
}

// Overloaded "operator ->" for class "iterator"
template <typename K, typename V>
typename MyUnordered_map<K,V>::Cell *MyUnordered_map<K,V>::iterator::operator ->(){
    return this->cp;
}

// Overloaded "operator *" for class "iterator"
template <typename K, typename V>
typename MyUnordered_map<K,V>::Cell &MyUnordered_map<K,V>::iterator::operator *(){
    return *this->cp;
}

#endif // MYUNORDERED_MAP_H

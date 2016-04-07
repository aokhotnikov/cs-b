#ifndef MYBST_H
#define MYBST_H

template <typename T>
class MyBST{
    private:
        class Node{
            public:
                T data;
                Node *left;             // pointer to the left node
                Node *right;            // pointer to the right node
                Node(const T& value){
                    left = right = NULL;
                    this->data = value;
                }
        };
        int countElem;                   // the number of nodes
        Node *root;                      // root of the tree
        void add(Node *n, const T& data);
        void showBST(Node *n, int dash); // show all nodes
        void clear(Node *root);          // remove all nodes
    public:
        MyBST();
        ~MyBST();
        void remove(const T& data, Node *n = NULL); // remove node
        const T& findMin(Node *n = NULL);// search min value
        const T& findMax(Node *n = NULL);// search max value
        void sort(T *mas, int n);        // Tree sort
        bool contains(const T&);         // contains the value
        T& find(const T& data);          // search value
        const T& getRootData();          // root value
        void insert(const T&);           // add value to the tree
        bool empty() const;
        int size() const;
        T& removeMax();                  // remove max value
        T& removeMin();                  // remove min value
        void show();
};

// The constructor
template <typename T>
MyBST<T>::MyBST(){
    countElem = 0;
    root = nullptr;
}

// The destructor
template <typename T>
MyBST<T>::~MyBST(){
    clear(this->root);
}

/*
 * The method adds a node in a binary tree
*/
template <typename T>
void MyBST<T>::insert(const T &data){
    if (!contains(data)){
        if (root == NULL){
            root = new Node(data);
        }
        else{
            add(root, data);
        }
        countElem++;
    }
}
/*
 * The method recursively finds the parent and binds it to the new node
*/
template <typename T>
void MyBST<T>::add(Node *n, const T& data){
    if (n->data > data){
        if (n->left != NULL)
            add(n->left, data);
        else
            n->left = new Node(data);
    }
    if (n->data < data){
        if (n->right != NULL)
            add(n->right, data);
        else
            n->right = new Node(data);
    }
}
/*
 * The method checks for the nodes of a binary tree and
 * calls the output method on the screen
*/
template <typename T>
void MyBST<T>::show(){
    if(!empty()){
        showBST(root, 0);
    }
    else std::cout << "The container is empty!" << std::endl;
}
/*
 * The method recursively displays the nodes of a binary tree
*/
template <typename T>
void MyBST<T>::showBST(Node *n, int dash){
    dash += 3;
    if(n->left){
        showBST(n->left, dash);
    }
    for (int i = 0; i < dash; ++i) {
        std::cout << '-';
    }
    std::cout << "|" << n->data << "|" << std::endl;
    if(n->right){
        showBST(n->right, dash);
    }
}
/*
 * The method removes all elements from the container
*/
template <typename T>
void MyBST<T>::clear(Node *n){
    if (n != NULL) {
       clear(n->left);
       clear(n->right);
       delete n;
       countElem--;
    }
    root = NULL;
}
/*
 * The method returns the value of the root node
*/
template <typename T>
const T& MyBST<T>::getRootData(){
    return root->data;
}
/*
 * The method returns the minimum node value of the binary tree
*/
template <typename T>
const T& MyBST<T>::findMin(Node *node){
    Node *n = (node == NULL) ? root : node;
    while (n->left){
        n = n->left;
    }
    return n->data;
}
/*
 * The method returns the maximum node value of the binary tree
*/
template <typename T>
const T& MyBST<T>::findMax(Node *node){
    Node *n = (node == NULL) ? root : node;
    while (n->right){
        n = n->right;
    }
    return n->data;
}
/*
 * The method removes the smallest element of the binary search tree
 * and returns it
*/
template <typename T>
T& MyBST<T>::removeMin(){
    T data = findMin();
    remove(data);
    return data;
}
/*
 * The method removes the largest element of the binary search tree
 * and returns it
*/
template <typename T>
T& MyBST<T>::removeMax(){
    T data = findMax();
    remove(data);
    return data;
}
/*
 * The method shows an example of the implementation of sorting
 * algorithm using a binary tree
*/
template <typename T>
void MyBST<T>::sort (T *mas, int n){
    clear(root);
    for (int i = 0; i < n; i++){
        insert(mas[i]);
    }
    n = countElem;
    for (int i = 0; i < n; i++){
        mas[i] = removeMin();
    }
}

/*
 * The method checks whether or not there is a value in a binary tree
*/
template <typename T>
bool MyBST<T>::contains(const T& data){
    Node *n = root;
    while (n != NULL){
        if(data == n->data)
            return true;
        else if(data > n->data)
            n = n->right;
        else if(data < n->data)
            n = n->left;
    }
    return false;
}
/*
 * The method finds the value in a binary tree and returns it.
 * If not found, returns a root value
*/
template <typename T>
T& MyBST<T>::find(const T& data){
    Node *n = root;
    while (n != NULL){
        if(data == n->data)
            return n->data;
        else if(data > n->data)
            n = n->right;
        else if(data < n->data)
            n = n->left;
    }
    return root->data;
}
/*
 * The method finds the node by value and removes node from a binary tree.
 * There are 3 possible situations:
 * 1. The node has no children - his parent pointer = NULL
 * 2. The node has only a left(or right) child - his parent pointer = child pointer
 * 3. The node has two children - finds the maximum value in the left subtree(or
 *    minimum in the right subtree), copies the value in the current node and
 *    the found node is removed
*/
template <typename T>
void MyBST<T>::remove(const T& data, Node *currentNode){
    Node *parent, *n;
    currentNode == NULL ? parent = n = root : parent = n = currentNode;

    while (n != NULL){
        if(data == n->data){
            // 1. no children(leaf)
            if (n->left == NULL && n->right == NULL){
                parent->left == n ? parent->left = NULL : parent->right = NULL;
                if (root == n) root = NULL;
            }
            // 2. right child only
            else if (n->left == NULL){
                parent->left == n ? parent->left = n->right : parent->right = n->right;
                if (root == n) root = n->right;
            }
            // 2. left child only
            else if (n->right == NULL){
                parent->left == n ? parent->left = n->left : parent->right = n->left;
                if (root == n) root = n->left;
            }
            // 3. two children
            else{
                T data = findMax(n->left);//or findMin(n->right)
                remove(data, n);          //run the recursion(n - current node)
                n->data = data;
                break;
            }
            delete n;
            n = NULL;
            countElem--;
        }
        else if(data > n->data){
            parent = n;
            n = n->right;
        }
        else if(data < n->data){
            parent = n;
            n = n->left;
        }
    }
}
/*
 * Тhe method determines the BST size
 * @return Тhe number of elements in the BST
*/
template <typename T>
int MyBST<T>::size() const{
    return countElem;
}
/*
 * The method returns true if the BST is empty
*/
template <typename T>
bool MyBST<T>::empty() const{
    return size() == 0;
}

#endif // MYBST_H

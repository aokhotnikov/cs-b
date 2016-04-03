#include <iostream>
#include "tree.h"

using namespace std;

//The constructor Node class
Node::Node(int count, char name, Node *l, Node *r){
    this->count = count;
    this->name = name;
    this->l = l;
    this->r = r;
}

Node::~Node(){
    this->count = -1;
    this->name = '\0';
    this->l = NULL;
    this->r = NULL;
}

//The overload operator <(for sort)
bool Node::operator <(Node node){
    return this->count < node.count;
}

//The overload operator >(for sort)
bool Node::operator >(Node node){
    return this->count > node.count;
}

//The overload operator ==(for sort)
bool Node::operator ==(Node node){
    return this->count == node.count;
}
/*
 * The constructor Tree class creates a tree of nodes using Huffman algorithm
 *
 * @param listNode The node list sorted in ascending
*/
Tree::Tree(MyList<Node> *listNodes){
    while(listNodes->size() >= 2){
        Node node = listNodes->front();
        Node *l = new Node(node.count, node.name, node.l, node.r);
        listNodes->pop_front();
        node = listNodes->front();
        Node *r = new Node(node.count, node.name, node.l, node.r);
        listNodes->pop_front();
        Node *newNode = new Node(l->count + r->count, '\0', *&l, *&r);

        MyList<Node> :: iterator it = listNodes->begin();
        while (it <= listNodes->end()){
            if(newNode->count <= it->count){
                listNodes->insert(it, *newNode);
                break;
            }
            it++;
        }
        if (it > listNodes->end()){
            listNodes->insert(it, *newNode);
        }
    }
}
/*
 * The method returns a string of characters that is translated into binary code
 *
 * @param charStr The character string
 * @param node The root node of the tree
 * @return The binary character string
*/
string Tree::getBinaryString(string *charStr, Node *node){

    fillBinaryMap(node); //creates binary symbol alphabet(this->binMap)

    string binaryStr;
    for (size_t i = 0; i < charStr->size(); i++){
        binaryStr += this->binMap[charStr->at(i)];
    }

    return binaryStr;
}
/*
 * The method recursively traverses the binary tree according to the algorithm:
 * the left turn to binary string add 0, a right turn -1;
 * if the found tree node, adding the resulting binary string and the node name in the mapping table,
 * then delete the last character binary strings, and take a step back
 *
 * @param node The node of the tree
 * @param str The binary string
*/
void Tree::fillBinaryMap(Node *node, string str){
    if (node != NULL) {
        if (node->l != NULL) {
            fillBinaryMap(node->l, str += "0");
            str.erase(str.size() - 1, 1); //removes the last character of the string
        }
        if (node->r != NULL) {
            fillBinaryMap(node->r, str += "1");
            str.erase(str.size() - 1, 1); //removes the last character of the string
        }
        if ((node->l == NULL) && (node->r == NULL)){
            this->binMap[node->name] = str;
        }
    }
}
/*
 * The mthod converts a binary string to a character string
 *
 * @param node The root node of the tree
 * @param strBits The binary string
 * @return The decode character string
*/
string Tree::getDecodeString(Node *node, string strBits){
    MyQueue<char> *stringBits = new MyQueue<char>();

    for (size_t i = 0; i < strBits.size(); i++){
        stringBits->push(strBits[i]);
    }
    while (stringBits->size() > 7){
        searchSymbol(node, stringBits);
    }

    delete stringBits;

    return this->decodeText;
}
/*
 * The method goes in the binary tree and finds a node that has no descendants,
 * than adds to a class field 'decodeText' node symbol
 *
 * @param node The node of the tree
 * @param strBits The binary string
*/
void Tree::searchSymbol(Node *node, MyQueue<char> *strBits){
    if (node != NULL) {
        if ((node->l != NULL) && (strBits->front() == '0')){
            strBits->pop();
            searchSymbol(node->l, strBits);
            return;
        }
        if ((node->r != NULL) && (strBits->front() == '1')){
            strBits->pop();
            searchSymbol(node->r, strBits);
            return;
        }
        if ((char(254) == node->name) && (strBits->size() <= 7 )){ //char(254) - pseudo-EOF character
            return;
        }
        this->decodeText += node->name;
    }
}
/*
 * The method recursively displays the nodes of a binary tree(was used to Debag)
 *
 * @param node The node of the tree
 * @param dash The visualization parameter
*/
void Tree::show(Node *node, int dash){
    if (node != NULL){
       dash += 2;
       show(node->l, dash); //Recursion to display the left child
       show(node->r, dash); //Recursion to display the right child
       for (int i = 0; i < dash; i++){
           cout << "-";
       }
       cout << "|count:" << node->count << " name:" << node->name << endl; //show node
    }
}
/*
 * The method recursively deletes the nodes of a binary tree
 *
 * @param node The node of the tree
*/
void Tree::deleteTree(Node *node){
    if (node != NULL) {
       deleteTree(node->l);
       deleteTree(node->r);
       delete node;
    }
}

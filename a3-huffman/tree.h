#ifndef TREE_H
#define TREE_H

#include <string>
#include "myqueue.h"
#include "mylist.h"
#include "myunordered_map.h"

class Node {

    public:

        int count;
        char name;
        Node *l,*r;

        //The constructor
        Node(int count = -1, char name = '\0', Node *l = NULL, Node *r = NULL);

        //The destructor
        ~Node();

        //The overload operator <(for sort)
        bool operator <(Node node);
        //The overload operator >(for sort)
        bool operator >(Node node);
        //The overload operator ==(for sort)
        bool operator ==(Node node);
};

class Tree{

    private:

        MyUnordered_map<char, std::string> binMap; //binary symbol alphabet

        std::string decodeText; //decode string

        //The method traverses the tree and fills the class field "binMap"
        void fillBinaryMap(Node *node, std::string str = "");

        //The method traverses the tree and fills the class field "decodeText"
        void searchSymbol(Node *node, MyQueue<char> *strBits);

    public:

        //The constructor creates a tree of nodes using Huffman algorithm
        Tree(MyList<Node> *listNodes);

        //The method returns a string of characters that is translated into binary code
        std::string getBinaryString(std::string *charStr, Node *node = NULL);

        //The method converts a binary string to a character string
        std::string getDecodeString(Node *node = NULL, std::string strBits = "");

        //The method recursively displays the nodes of a binary tree(was used to Debag)
        static void show(Node *node = NULL, int dash = 0);

        //The method recursively deletes the nodes of a binary tree
        void deleteTree(Node *node = NULL);
};

#endif // TREE_H

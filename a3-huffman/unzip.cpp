#include <iostream>
#include <fstream>
#include <bitset>
#include "unzip.h"

using namespace std;

/*
 * The method reads from the archive the nodes of a binary tree and creates a list of nodes,
 * than reads binary string of characters
 *
 * @param listNode The list of nodes
 * @param fileName The archive file that will be read
 * @return The binary string of characters
*/
string readArchive(MyList<Node> *listNode, string fileName){
    string strBits;
    ifstream fin(fileName, ios_base::in | ios_base::binary);
    if (fin.is_open()){
        unsigned int countSymbols = 0;
        bool isTree = true;
        bool isChar = true;
        char symbol, byte;
        string countChar;

        while(fin.read((char*)&byte,sizeof (byte))){

            if (isTree) {
                if ((byte == char(254)) && (countSymbols == 0) && isTree) {
                    isTree = false;
                    continue;
                }
                if (countSymbols == 0) {
                    if (byte != char(166))
                        countChar += byte;
                    else{
                        countSymbols = atoi(countChar.c_str());
                        countChar = "";
                    }
                    continue;
                }
                if (isChar){
                    symbol = byte;
                    isChar = false;
                }
                else if (byte != '|')
                    countChar += byte;
                else {
                    Node node(atoi(countChar.c_str()), symbol);
                    listNode->push_back(node);
                    countSymbols--;
                    countChar = "";
                    isChar = true;
                }
                continue;
            }
            bitset<8> bits = byte;
            strBits += bits.to_string();
        }
        fin.close();
    }
    else{
        cout << "ERROR!!! The file " << fileName << " can not be opened";
        exit(0);
    }
    return strBits;
}
/*
 * The method unzips a file that was previously archived on Huffman algorithm
 *
 * @param listNode The list of nodes
 * @param strBits The binary string of characters
 * @param fileName The file to which we write
*/
void decompression(MyList<Node> *listNode, string strBits, string fileName){

    Tree tree(*&listNode);//creates a binary tree
    //Tree::show(&listNode->front()); // for DEBAG
    string symbolsFromTree = tree.getDecodeString(&listNode->front(), strBits);
    tree.deleteTree(&listNode->front());

    ofstream fail(fileName, ios_base::out | ios_base::binary);
    if (fail.is_open()) {
        fail << symbolsFromTree;
        fail.close();

        cout << "the archive is unpacked into the file '" << fileName << "'";
    }
    else{
        cout << "ERROR!!! The file " << fileName << " can not be created";
        exit(0);
    }
}

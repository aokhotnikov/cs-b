#include <iostream>
#include <fstream>
#include <bitset>
#include "zip.h"

using namespace std;

/*
 * The method reads the file and returns a string of characters
 *
 * @param fileName The file to be read
 * @return The character string
*/
string readFile(string fileName){
    ifstream file(fileName, ios_base::in | ios_base::binary);
    string charStr;
    if (file.is_open()) {
        char byte;
        while(file.read((char*)&byte,sizeof (byte))){
            charStr += byte;
        }
        charStr += char(254);//add end-symbol
        file.close();
    }
    else{
        cout << "ERROR!!! The file " << fileName << " can not be opened";
        exit(0);
    }
    return charStr;
}
/*
 * The method takes a string of characters and for each character calculates the char frequency.
 * Than creates a list of nodes for binary tree
 *
 * @param charStr The character string
 * @return The list of nodes sorted by char frequency
*/
MyList<Node> createListNode(string *charStr){
    MyUnordered_map<char, int> symbols;
    for (size_t i = 0; i < charStr->size(); i++){
        symbols[charStr->at(i)] = 0;
    }

    for (size_t i = 0; i < charStr->size(); i++){
        symbols[charStr->at(i)]++;
    }

    MyList<Node> listNode;
    for (auto it = symbols.begin(); it != symbols.end(); ++it){
        Node node(it -> value, it -> key);
        listNode.push_back(node);
    }
    listNode.sort();
    return listNode;
}
/*
 * The method creates a file, which writes data to recreate the binary tree and the encoded bit sequence.
 * The file will result in the sequence of symbols:
 * 35(askii166)r23|t12|a4|g5....|(askii254)1010010010101010...1010
 *
 * @param listNode The list of nodes
 * @param charStr The character string
 * @param archiveName The archive name
*/
void createArchive(MyList<Node> *listNode, string *charStr, string archiveName){
    ofstream fout(archiveName, ios_base::out | ios_base::binary | ios_base::trunc);
    if (fout.is_open()) {

        // -----------write to the file TREE--------------

        fout << listNode->size() << char(166);// number of tree nodes
        for(auto it = listNode->begin(); it <= listNode->end(); it++){
            fout <<  it->name << it->count << '|';
        }
        fout << char(254); // The boundary between the tree and BinaryString(bits)

        // -----------write to the file BinaryString------

        string binaryStr = createBinaryString(*&listNode, *&charStr);
        writeBinaryString(fout, binaryStr);

        fout.close();

        cout << "archive " << archiveName << " created";

    }else{
        cout << "ERROR!!! The file " << archiveName << " can not be created";
        exit(0);
    }
}
/*
 * The method creates a binary tree, and returns a binary string of characters
 *
 * @param listNode The list of nodes
 * @param charStr The character string
 * @return The binary string of characters
*/
string createBinaryString(MyList<Node> *listNode, string *charStr){
    Tree tree(*&listNode);//creates a binary tree
    //Tree::show(&listNode->front()); // for DEBAG
    string binaryStr = tree.getBinaryString(*&charStr, &listNode->front());
    tree.deleteTree(&listNode->front());

    return binaryStr;
}
/*
 * The method splits the bits byte by byte and writes to a file
 *
 * @param fout The output file stream
 * @param binaryStr The binary string of characters
*/
void writeBinaryString(ofstream & fout, string binaryStr){
    for (size_t j = 0; j < binaryStr.size(); j+=8) {
        string bits8 = binaryStr.substr(j, 8);
        bitset<8> bits(bits8);
        if (bits8.size() < 8)
            bits <<= (8 - bits8.size()); // add to byte zero bits(for last byte)
        char byte = bits.to_ulong();
        fout << byte;
    }
}

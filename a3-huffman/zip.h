#ifndef ZIP_H
#define ZIP_H

#include <tree.h>

// The method reads the file and returns a string of characters
std::string readFile(std::string fileName);

// The method takes a string of characters and for each character calculates the char frequency.
// Than creates a list of nodes for binary tree
MyList<Node> createListNode(std::string *charStr);

// The method creates a file, which writes data to recreate the binary tree and the encoded bit sequence.
void createArchive(MyList<Node> *listNode, std::string *charStr, std::string archiveName = "Archive.huff");

// The method creates a binary tree, and then creates a binary symbol alphabet,
// after each character gets a binary code
std::string createBinaryString(MyList<Node> *listNode, std::string *charStr);

//The method splits the bits byte by byte and writes to a file
void writeBinaryString(std::ofstream & fout, std::string binaryStr);

#endif // ZIP_H

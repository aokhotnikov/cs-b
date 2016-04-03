#ifndef UNZIP_H
#define UNZIP_H

#include <tree.h>

//The method reads from the archive the nodes of a binary tree and creates a list of nodes,
//than reads binary string of characters
std::string readArchive(MyList<Node> *listNode, std::string fileName);

//The method unzips a file that was previously archived on Huffman algorithm
void decompression(MyList<Node> *listNode, std::string strBits,std::string fileName = "DecompressionFile");

#endif // UNZIP_H

#include <iostream>
#include <cstring>
#include <time.h>
#include "zip.h"
#include "unzip.h"

using namespace std;

int main(int argc, char *argv[]){

    if (argc > 1){

        if(!stricmp(argv[1],"-z")){

            if (argc > 2){
                clock_t t = clock();

                string charStr = readFile(argv[2]);
                MyList<Node> listNode = createListNode(&charStr);
                argc > 3 ? createArchive(&listNode, &charStr, argv[3]) : createArchive(&listNode, &charStr);

                double time = (clock() * 1.0 - t)/CLOCKS_PER_SEC;
                cout << fixed << " for " << time << " second" << endl;
            }
            else cout << "no 'filename' parameter" << endl;
        }
        if(!stricmp(argv[1],"-u")){
            if (argc > 2){
                clock_t t = clock();

                MyList<Node> listNode;
                string strBits = readArchive(&listNode, argv[2]);
                argc > 3 ? decompression(&listNode, strBits, argv[3]) : decompression(&listNode, strBits);

                double time = (clock() * 1.0 - t)/CLOCKS_PER_SEC;
                cout << fixed << " for " << time << " second" << endl;
            }
            else cout << "no 'archivename' parameter" << endl;
        }
    }
    else{
        cout << "to create an archive, you should enter from the console: -z filename archivename" << endl;
        cout << "to unzip you should enter from the console: -u archivename filename" << endl;
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include "mystack.h"
//#include "myqueue2.h"
#include "myqueue.h"
#include "myvector.h"
#include "mylist.h"
#include "mybst.h"
#include "myunordered_map.h"
#include <ctime>

using namespace std;

class Node {
    public:
        int count;
        char name;
        //The constructor
        Node(int count = -1, char name = '\0'){
            this->count = count;
            this->name = name;
        }
        //The overload operator <(for sort)
        bool operator <(Node node){
            return this->count < node.count;
        }
        //The overload operator >(for sort)
        bool operator >(Node node){
            return this->count > node.count;
        }
        //The overload operator ==(for sort)
        bool operator ==(Node node){
            return this->count == node.count;
        }
};

//The overload operator <<(for show)
ostream &operator <<(ostream &os,  const Node &m) {
    return os << m.count << " " << m.name;
}

MyList<Node> createListNode(){
    MyList<Node> listNode;
    listNode.push_back(Node(1, 'z'));
    listNode.push_back(Node(2, 'x'));
    listNode.push_back(Node(3, 'c'));
    return listNode;
}

int main(){

//------------------------ MyStack ------------------------
//    MyStack<string> stack;
//    stack.push("a");
//    stack.pop();
//    if (stack.empty())
//        stack.push("a");
//    stack.push("b");
//    stack.push("c");
//    string c = stack.top();
//    stack.pop();
//    stack.push(c);
//    stack.push("d");
//    if (stack.size() == 4)
//        stack.push("e");
//    cout << "=========== show stack ==============" << endl;
//    stack.show();

//------------------------ MyQueue  ----------------------
//    int a = 99;
//    MyQueue <int> queue;
//    if (queue.empty())
//        queue.push(a);
//    queue.push(0);
//    queue.pop();
//    queue.push(1);
//    queue.push(2);
//    queue.pop();
//    queue.push(3);
//    queue.push(4);
//    queue.push(5);
//    queue.pop();
//    queue.push(6);
//    queue.push(7);
//    queue.push(8);
//    queue.push(9);
//    //queue.push(10);
//    cout << "=========== show queue ==============" << endl;
//    queue.show();

//------------------------ MyQueue 2------------------------
//    Node a = Node(1, 'a');
//    MyQueue <Node> queue;
//    queue.push(a);
//    queue.pop();
//    if(queue.empty())
//        queue.push(Node(2, 'b'));
//    queue.push(Node(3, 'c'));
//    queue.push(Node(4, 'd'));
//    cout << "front: " << queue.front() << endl; // 2
//    cout << "back: " << queue.back() << endl;   // 4
//    queue.pop();
//    Node n = queue.front();
//    cout << n.name << endl; // c
//    queue.push(Node(5, 'e'));
//    cout << "=========== show queue 2 ==============" << endl;
//    cout << "size: " << queue.size() << endl;
//    queue.show();

//------------------------ MyVector ---------------------------
//    MyVector<string> v(2);
//    MyVector<string> vv(2);
//    v[0] = "a";
//    vv[0] = "aa";
//    if (v == vv) cout << "v = vv" << endl;
//    if (v != vv) cout << "v != vv" << endl;
//    v = vv;
//    v.show();
//    cout << "----------------------------" << endl;
//    v.remove(1);
//    v.push_back("bb");
//    v.show();
//    cout << "front: " << v.front() << endl;
//    cout << "back: " << v.back() << endl;
//    cout << "----------------------------" << endl;
//    v.insert(0, "a");
//    v[1] = "b";
//    v.pop_back();
//    v.push_back("c");
//    v.show();
//    cout << "1 el: " << v[0] << endl;
//    cout << "2 el: " << v.at(1) << endl;
//    cout << "----------- v2 = v ---------" << endl;
//    vv = v;
//    vv.show();
//    cout << "----------- new vv ---------" << endl;
//    vv.clear();
//    vv.push_back("aa");
//    vv.push_back("bb");
//    vv.push_back("cc");
//    vv.show();
//    cout << "------------ [][] ----------" << endl;
//    MyVector<MyVector<string>> mas;
//    mas.push_back(v);
//    mas.push_back(vv);
//    mas.push_back(vv);
//    mas.push_back(v);
//    mas.pop_back();
//    mas.pop_back();
//    mas.push_back(vv);
//    mas.push_back(v);
//    for (int i = 0; i < mas.size(); i++){
//        for (int j = 0; j < mas[i].size(); j++){
//            cout << mas[i][j] << "  ";
//        }
//        cout << endl;
//    }

//------------------------ MyList---------------------------
//    MyList<Node> list;
//    list.push_back(Node(1, 'a'));
//    list.pop_front();
//    list.push_front(Node(2, 'b'));
//    list.push_front(Node(1, 'a'));
//    list.insert(2, Node(3, 'c'));//insert without iterator
//    list.push_back(Node(4, 'd'));
//    list.push_back(Node(5, 'e'));
//    list.pop_back();
//    list.insert(++list.end(), Node(5, 'e'));//insert using iterator
//    cout << "=============== Show LIST =================" << endl;
//    cout << "size: " << list.size() << endl;
//    list.show();
//    Node first = list.front();
//    Node last = list.back();
//    cout << "first: " << first.name << endl << "last: " << last.name << endl;
//    cout << "getElemData(1): " << list.getElemData(1) << endl;
//    list.clear();
//    cout << "size after clear(): " << list.size() << endl;
//    cout << "=============== <SORT list> ===============" << endl;
//    list.push_back(Node(21, 'f'));
//    list.push_back(Node(5, 'b'));
//    list.push_back(Node(45, 'i'));
//    list.push_back(Node(5, 'b'));
//    list.push_back(Node(58, 'k'));
//    list.push_back(Node(16, 'e'));
//    list.push_back(Node(2, 'a'));
//    list.push_back(Node(33, 'h'));
//    list.push_back(Node(22, 'g'));
//    list.push_back(Node(55, 'j'));
//    list.push_back(Node(7, 'c'));
//    list.push_back(Node(11, 'd'));
//    cout << "size: " << list.size() << endl;
//    //list.sort();  // without parameters(min-max)
//    auto begin = list.begin();
//    auto end = list.end();
//    list.sort(begin, end);
//    for (MyList<Node> :: iterator it2 = begin; it2 <= end; it2++){
//        cout << it2->count << " " << it2->name << endl;
//    }
//    cout << "=============== <iterator> ================" << endl;
//    auto it = list.begin();
//    it = it + 3;
//    cout << "it + 3:   " << it->name << endl;
//    it = it - 1;
//    cout << "it - 1:   " << it->name << endl;
//    it++;
//    cout << "  it++:   " << it->name << endl;
//    ++it;
//    cout << "  ++it:   " << it->name << endl;
//    cout << "     *:" << *it << endl;
//    cout << "     &:" << &it << endl;
//    cout << "=============== <createListNode> ================" << endl;
//    MyList<Node> list2 = createListNode();
//    list = list2;
//    list.show();
//------------------------ MyUnordered_map---------------------------
//    MyUnordered_map<string,int> mymap;
//    mymap.at("a") = 0;  mymap.at("b") = 1;
//    mymap.at("c") = 2;  mymap["d"] = 3;
//    mymap["e"] = 4;     mymap["f"] = 5;
//    mymap["g"] = 6;     mymap["h"] = 7;
//    mymap["i"] = 8;     mymap["j"] = 9;
//    mymap["k"] = 10;    mymap["l"] = 11;
//    cout << "=============== MyUnordered_map ===============" << endl;
//    mymap.show();

//    mymap["m"] = 12;    mymap["n"] = 13;
//    mymap["o"] = 14;    mymap["p"] = 15;
//    mymap["q"] = 16;    mymap["r"] = 17;
//    mymap["s"] = 18;    mymap["t"] = 19;
//    mymap["u"] = 20;    mymap["v"] = 21;
//    mymap["w"] = 22;    mymap["x"] = 23;
//    mymap.add("y", 24); mymap.at("z") = 25;
//    cout << "=========== after expandNumBuckets =============" << endl;
//    mymap.show();

//    if (mymap.containsKey("d"))
//        cout << "[d] contains in hashmap" << endl;
//    mymap.remove("d");
//    mymap.remove("d");//show - [d] is missing
//    cout << "=============== after remove [d] ===============" << endl;
//    mymap.show();

//    mymap.clear();
//    mymap["("] = 25;
//    mymap[")"] = 26;
//    mymap["-"] = 27;
//    mymap["-"]++;
//    cout << "==================== iterator ==================" << endl;
//    for (auto it = mymap.begin(); it != mymap.end(); ++it){
//        cout << "[" << it->key << "]=" << it->value << endl;
//    }
//    auto it = mymap.begin();
//    it->value = 555;
//    cout << "========== re assignment iterator ==============" << endl;
//    cout << "[" << it->key  << "]=" << it->value << endl;
//    cout << "[" << (*it).key  << "]=" << (*it).value << endl;

//---------------------------MyBST------------------------------
    MyBST<int> tree;
//    srand(time(0));
//    for (int i = 0; i < 20; ++i) {
//        tree.insert(rand() % 100);
//    }
//    tree.show();
    tree.insert(50);
    tree.insert(25);
    tree.insert(75);
    tree.insert(20);
    tree.insert(30);
    tree.insert(85);
    tree.insert(70);
    tree.insert(5);
    tree.insert(15);
    tree.insert(18);
    tree.insert(81);
    cout << "=================== MyBST ===================" << endl;
    tree.show();
    cout << "root - " << tree.getRootData() << endl;
    cout << "min - " << tree.findMin() << endl;
    cout << "max - " << tree.findMax() << endl;
    tree.remove(20);
    cout << tree.removeMin() << endl;
    cout << tree.removeMax() << endl;
    cout << "============= MyBST after remove ============" << endl;
    tree.show();
    cout << "================= tree sort =================" << endl;
    srand(time(0));
    int mas[10];
    for (int i = 0; i < 10; ++i) {
        mas[i] = rand() % 1000;
        cout << mas[i] << " ";
    }
    cout << endl;
    tree.sort(*&mas, 10);
    for (int i = 0; i < 10; ++i) {
        cout << mas[i] << " ";
    }

    return 0;
}

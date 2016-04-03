#include <iostream>
#include <algorithm>
#include <regex>
#include "calculator.h"
#include "validation.h"

using namespace std;

void initArgument(string & task, string nameArg, string argConsol);
void initPriority(MyUnordered_map<string, int> & priority);

int main(int argc, char* argv[])
{
    string task = "";
    if (argc > 1)
        task = argv[1];
    else {
        while(true){
            cout << "Enter the expression: ";
            getline(cin, task);
            if (task.size() != 0) break;
        }
    }

    transform(task.begin(), task.end(), task.begin(), ::tolower);

    if (regex_search(task, regex("(?!t)a(?!n)")))
        argc > 2 ? initArgument(task, "a", argv[2]) : initArgument(task, "a", "");

    if (regex_search(task, regex("b")))
        argc > 3 ? initArgument(task, "b", argv[3]) : initArgument(task, "b", "");

    if (regex_search(task, regex("c(?!os)")))
        argc > 4 ? initArgument(task, "c", argv[4]) : initArgument(task, "c", "");

    cout << "Your arithmetic expression:  " << task << endl;
    if (checkValidation(task)) {
        cout << "Expression after validation: " << task << endl;

        //The priorities of the arithmetic operations
        MyUnordered_map<string, int> priority;
        initPriority(priority);

        MyStack <string> operators;
        MyStack <double> operands;
        int pos = 0;
        double rez = getRez(task, operators, operands, priority, &pos);
        cout << "---------------------------------------------" << endl;
        cout << "Result: " << rez << endl;
    }

    return 0;
}

/* Method replaces the variables "a", "b", "c" in the arguments that entered from the console
 *
 * @param task  The arithmetic expression
 * @param nameArg The name of the argument
 * @param argConsol An argument is entered from the console
*/
void initArgument(string & task, string nameArg, string argConsol){
    if (argConsol.size() == 0){
        cout << "Enter the argument \"" << nameArg << "\": ";
        getline(cin, argConsol);
    }
    if (nameArg == "a")
        task = regex_replace(task, regex("(?!t)a(?!n)"), "(" + argConsol + ")");
    else if (nameArg == "b")
        task = regex_replace(task, regex("b"),           "(" + argConsol + ")");
    else
        task = regex_replace(task, regex("c(?!os)"),     "(" + argConsol + ")");
}

/* The method assigns arithmetic operations priorities
 *
 * @param priority The container arithmetic operations
*/
void initPriority(MyUnordered_map<string, int> & priority){
    priority["("] = 1;     priority[")"] = 1;
    priority["+"] = 2;     priority["-"] = 2;
    priority["*"] = 3;     priority["/"] = 3;
    priority["^"] = 4;     priority["R"] = 5;
    priority["S"] = 5;     priority["C"] = 5;
    priority["T"] = 5;     priority["L"] = 5;
}

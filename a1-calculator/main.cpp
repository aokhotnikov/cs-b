#include <iostream>
#include <algorithm>
#include <regex>
#include "calculator.h"
#include "validation.h"

using namespace std;


void initArguments(string & task, int argc, char* argv[]);

void replaceVariable(string & task, string var, string val, size_t pos = 0);

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

    initArguments(task, argc, argv); // a, b, c, ... z

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

/* The method replaces the variables on the values that
 * are entered from the console or from the command line
 *
 * @param task The arithmetic expression
 * @param argc The number of command line arguments
 * @param argv An array of arguments from the command line
*/
void initArguments(string & task, int argc, char* argv[]){
    string var, val;
    for (int i = 2; i < argc; ++i){
        string argConsol = argv[i];   // b=77 or y=44.6 or ...
        var = argConsol.substr(0, 1); // variable
        val = argConsol.substr(2);    // value

        replaceVariable(task, var, val);
    }
    for (size_t i = 0; i < task.size(); ++i){
        if (isalpha(task[i]) && !isalpha(task[i + 1]) && !isalpha(task[i - 1])){
            var = task[i];
            cout << "Enter the argument \"" << var << "\": ";
            getline(cin, val);

            replaceVariable(task, var, val, i);
        }
    }
}

/* The method replaces the variable by the value
 *
 * @param task  The arithmetic expression
 * @param var The variable (any letter from a to z)
 * @param val The value of the variable
 * @param pos The position in the expression with which the variable should be replaced
*/
void replaceVariable(string & task, string var, string val, size_t pos){
    while (pos != string::npos){
        if (!isalpha(task[pos - 1]) && !isalpha(task[pos + 1])){
            task.replace(pos, 1, "(" + val + ")");
        }
        pos = task.find(var, pos + 1);
    }
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

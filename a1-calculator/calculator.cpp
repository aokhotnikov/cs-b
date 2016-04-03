#include <iostream>
#include <cmath>
#include "calculator.h"

using namespace std;

/*
 * The method in a loop from the beginning to the end of the expression
 * performs mathematical operations on operands. If it finds an opening
 * bracket, then the method calls itself (recursion)
 *
 * @param task  The arithmetic expression
 * @param operators The operators stack
 * @param operands The operand stack
 * @param priority The priorities of the arithmetic operations
 * @param pos The loop position
 * @return The result of computing the expression
*/
double getRez(string task, MyStack<string> & operators, MyStack<double> & operands, MyUnordered_map<string, int> & priority, int* pos){

    int length = task.length();
    string operations = "+-*/^SCTLR";
    string symbols = "SCTLR";
    double rez = 0;

    for (int i = *pos; i < length; i++){

        if (task[i] == '(') {
            *pos = i + 1;
            operators.push("(");    //add stack
            operands.push(getRez(task, operators, operands, priority, &*pos));  //add stack recursion
            i = *pos;
        }

        if (operations.find(task[i]) != string::npos){  //task[i] in "+-*/^SCTLR"

            if ((task[i - 1] != ')') && (symbols.find(task[i]) == string::npos)){//task[i] not in "SCTLR"
                operands.push(atof(task.substr(*pos, i - *pos).c_str()));        //add operand
            }
            //while stack operators not NULL
            while ((!operators.empty()) && (priority.at(task.substr(i, 1)) <= priority.at(operators.top()))){
                calculate(operators, operands);
            }
            operators.push(task.substr(i, 1));  //add operation
            *pos = i + 1;
        }

        //end string or ')'
        if ((i >= length - 1) || (task[i] == ')')){

            if (task[i - 1] != ')'){
                operands.push(atof(task.substr(*pos, i).c_str()));
            }
            while ((!operators.empty()) && (operators.top() != "(")){
                calculate(operators, operands);
            }
            if (task[i] == ')'){
                operators.pop();
                *pos = i + 1;
                break;  //exit of the recursion
            }
        }
    }
    rez = operands.top();
    operands.pop();
    return rez;
}

/*
 * The method performs arithmetic operations on operands
 *
 * @param operators The operators stack
 * @param operands The operand stack
*/
void calculate(MyStack<string> & operators, MyStack<double> & operands){
    string op = operators.top();
    double num2 = operands.top();
    operands.pop();

    if(op == "R"){                  //sqrt
        try {
            if (num2 < 0) throw string("ERROR! Root of a negative number!");
            operands.push(sqrt(num2));
        }
        catch(string &ex) {
            cout << ex;
            exit(0);
        }
    }
    else if(op == "S")              //sin
        operands.push(sin(num2));
    else if(op == "C")              //cos
        operands.push(cos(num2));
    else if(op == "T")              //tan
        operands.push(tan(num2));
    else if(op == "L")              //log
        operands.push(log(num2));
    else {

        double num1 = operands.top();
        operands.pop();

        if(op == "/"){
            if (num2 != 0)
                operands.push(num1 / num2);
            else{
                cout << "ERROR! Division by zero!";
                exit(0);
            }
        }
        else if(op == "-")
            operands.push(num1 - num2);
        else if(op == "*")
            operands.push(num1 * num2);
        else if(op == "+")
            operands.push(num1 + num2);
        else if(op == "^")
            operands.push(pow(num1, num2));
    }
    operators.pop();
}

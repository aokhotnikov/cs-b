#include <iostream>
#include <regex>
#include "validation.h"

using namespace std;

/*
 * The method checks the expression for validity
 *
 * @param task  The arithmetic expression
*/
bool checkValidation(string & task){
    task = regex_replace(task, regex(" "), ""); //clear spases
    task = regex_replace(task, regex(","), ".");// ',' -> '.'

    //  Nsin -> N*sin     (-N)sin -> (-N)*sin      N(sin) -> N*(sin)
    task = regex_replace(task, regex ("([0-9]|[)])(sin|cos|tan|sqrt|log|\\()"), "$1*$2");
    task = regex_replace(task, regex ("([)])([0-9])"), "$1*$2"); // (N)N -> (N)*N

    smatch match;
    if ((regex_search(task, match, regex("[-/+*^][-/+*^]"))) ||
        (regex_search(task, match, regex("(sin|cos|tan|sqrt|log)(sin|cos|tan|sqrt|log)")))){

        cout << "ERROR! Between operators \"" << match[0] << "\" should be operand or brackets" << endl;
        return false;
    }

    int openBrackets = countSymbols(task,"(");
    int closeBrackets = countSymbols(task,")");
    if (openBrackets != closeBrackets){
        cout << "ERROR! The number of open brackets(" << openBrackets <<") is not equal to the number of closed brackets(" << closeBrackets << ")" << endl;
        return false;
    }

    task = regex_replace(task, regex("sin"), "S"); // 'sin' -> 'S'
    task = regex_replace(task, regex("cos"), "C"); // 'cos' -> 'C'
    task = regex_replace(task, regex("tan"), "T"); // 'tan' -> 'T'
    task = regex_replace(task, regex("log"), "L"); // 'log' -> 'L'
    task = regex_replace(task, regex("sqrt"), "R");//'sqrt' -> 'R'

    if (regex_search(task, regex("[^0-9-*()^/+.SCTLR]+"))){
        cout << "ERROR! Invalid symbol in the expression" << endl;
        return false;
    }

    return true;
}

/*
 * The method counts the number of the required characters in the string
 *
 * @param str The string in which searching the symbol
 * @param symbol The required symbol
*/
int countSymbols(string str, string symbol){
    int count = 0;
    smatch match;
    while (regex_search(str, match,  regex("["+symbol+"]")))
    {
        count++;
        str = match.suffix().str();
    }
    return count;
}

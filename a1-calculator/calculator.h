#ifndef CALCULATE_H
#define CALCULATE_H

#include <string>
#include "mystack.h"
#include "myunordered_map.h"

void calculate(MyStack<std::string> & operators, MyStack<double> & operands);

double getRez(std::string task, MyStack<std::string> & operators, MyStack<double> & operands,
              MyUnordered_map<std::string, int> & priority, int* pos);

#endif // CALCULATE_H

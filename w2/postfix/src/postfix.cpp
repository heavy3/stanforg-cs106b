#include <iostream>
#include "simpio.h"
#include "stack.h"
#include "console.h"

using namespace std;

const string OPERATORS = "+-*x/";   // allow x to be multiplication
const string SEPERATOR = " ";
void intro();
double evaluate(string express);
string nextToken(string &express);

int main() {

    intro();
    
    string express;
    double answer;
    do {
        express = getLine("Enter postfix expression (blank to quit): ");
        answer = evaluate(express);
        cout << "Answer is " << answer << endl;

    } while (express != "");    // in evaluate also has the same condition, but we pass by value :)

    return 0;
}

void intro() {
    cout << "A program to evaluate postfix expression: ex 5 4 * 8 2 / - 9 +" << endl;
}

double evaluate(string express) {
    Stack<double> numbers;

    while (express != "") {
        string token = nextToken(express);
        if (OPERATORS.find(token) == string::npos) {
            // next token is not an operator
            numbers.push(stringToDouble(token));
        } else {
            // the first number is below the second in the stack
            double second = numbers.pop();
            double first = numbers.pop();
            char op = stringToChar(token);

            switch (op) { // cant be a string
            case '+':
                numbers.push(first + second);
                break;
            case '-':
                numbers.push(first - second);
                break;
            case '/':
                numbers.push(first / second);
                break;
            default:
                numbers.push(first * second);
            }
        }
    }
    return numbers.pop();
}

string nextToken(string &express) {
    string token;

    int seperateLoc = express.find(SEPERATOR);
    if (seperateLoc != (int)string::npos) {
        token = express.substr(0, seperateLoc); // number can have vary length
        express = express.substr(seperateLoc + 1, express.size() - seperateLoc);
        return token;
    } else {
        // end of expression
        token = express;
        express = "";
        return token;
    }
}

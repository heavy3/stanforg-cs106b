#include <iostream>
#include "simpio.h"
#include "stack.h"
#include "console.h"
#include "vector.h"

using namespace std;

const string SEPERATOR = " ";

void intro();
Vector<int> parse(string word);
bool partitionable(Vector<int> &numbers);
bool partitionable(Vector<int> &numbers, int left, int right);

int main() {

    intro();
    string word;
    do {
        word = getLine("Enter a set of number (space seperate and at the end :)) to reduce (blank to quit): ");
        Vector<int> numbers = parse(word);
        cout << (partitionable(numbers) ? "True": "False") << endl;
    } while (word != "");    // in evaluate also has the same condition, but we pass by value :)

    return 0;
}

void intro() {
    cout << "A program to find out if a set of int can be partitionable: ex: {1,1,2,3,5} - > {1,2,3} and {1,5}" << endl;
}

Vector<int> parse(string word) {
    Vector<int> numbers;
    while (int sepLoc = word.find(SEPERATOR) != string::npos) {
        numbers.add(stringToInteger(word.substr(0, sepLoc)));
        word = word.substr(sepLoc + 1, word.length() - sepLoc);
    }

    cout << numbers.toString() << endl;
    return numbers;
}

bool partitionable(Vector<int> &numbers) {
    return partitionable(numbers, 0, 0);
}

bool partitionable(Vector<int> &numbers, int left, int right) {
    if (numbers.isEmpty()) {
        return left == right;
    } else {
        // get the first number
        int n = numbers[0];
        numbers.remove(0);
        bool answer = partitionable(numbers, left + n, right) || partitionable(numbers, left, right + n);
        // restore the first number
        numbers.insert(0, n);
        return answer;
    }
}




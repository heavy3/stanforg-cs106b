#include <iostream>
#include "simpio.h"
#include "stack.h"
#include "console.h"
#include "lexicon.h"
#include "filelib.h"

using namespace std;

void intro();
void reduce(string s);
bool reduce(Stack<string> &stack, string s);

Lexicon english;

int main() {

    intro();
    english = Lexicon("dictionary.txt");
    
    string word;

    do {
        word = getLine("Enter a word to reduce (blank to quit): ");

        if (english.contains(word))
            reduce(word);
        else
            cerr << "Invalid word" << endl;
    } while (word != "");    // in evaluate also has the same condition, but we pass by value :)

    return 0;
}

void intro() {
    cout << "A program to print a reduciable word: ex: cart -> art -> at > a" << endl;
}

void reduce(string s) {
    Stack<string> stack;
    bool hasSolution = reduce(stack, s);
    stack.push(s);

    if (!hasSolution) {
        cout << "The word cant be reducible" << endl;
        return;
    }

    while (!stack.isEmpty()) {
        cout << stack.pop() << "->";
    }
    cout << endl;
}

bool reduce(Stack<string> &stack, const string s) {
    if (s.length() == 1) {
        // assume that single word is a valid word
        return true;
    } else {
        for (int i = 0, len = s.length(); i < len; i++) {
            string sub = s.substr(0, i) + s.substr(i+1);
            if (english.contains(sub) && reduce(stack, sub)) {
                // only add to the stack when sub is a valid word
                stack.push(sub);
                return true;
            }
        }
        // no more word, return
        return false;
    }
}

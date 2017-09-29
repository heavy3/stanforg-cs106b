#include <iostream>
#include "simpio.h"
#include "stack.h"
#include "console.h"
#include "lexicon.h"
#include "filelib.h"

using namespace std;

void intro();
void permute(string s);
void permute(string sofar, string remain);

Lexicon english;

int main() {

    intro();
    english = Lexicon("dictionary.txt");
    
    string word;

    do {
        word = getLine("Enter a set of letter (blank to quit): ");
        permute(word);
    } while (word != "");    // in evaluate also has the same condition, but we pass by value :)

    return 0;
}

void intro() {
    cout << "A program to print all valid permutation for a set of letter" << endl;
}

void permute(string s) {
    permute("", s);
}

void permute(string sofar, string remain) {
    if (remain == "") {
        if (english.contains(sofar)) {
            cout << sofar << endl;
        }
    }
    else {
        for (int i = 0, len = remain.length(); i < len; i++) {
            // get a random letter from set and add it to remain
            string remaining = remain.substr(0, i) + remain.substr(i+1);
            permute(sofar + remain[i], remaining);
        }
    }
}


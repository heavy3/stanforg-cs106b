// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "lexicon.h"
#include "queue.h"
#include "stack.h"
#include "set.h"

using namespace std;
const string alphabet("abcdefghigklmnopqrstuvwxyz");

void introduction();
void printResult(Stack<string> &result, string &first, string &second);
void printNoResult(string& first, string &second);
Stack<string>& clone(Stack<string> origin);

int main() {
    introduction();
    ifstream dictionaryStream;
    promptUserForFile(dictionaryStream, "Dictionary file name?", "Dont find that file");

    Lexicon english(dictionaryStream);

    while (true) {

        string first = toLowerCase(getLine("Word #1 (or Enter to quit):"));
        if (first == "")
            break;

        string second = toLowerCase(getLine("Word #2 (or Enter to quit):"));
        if (second == "")
            break;

        if (first.length() != second.length()) {
            cerr << "The two words must be the same length." << endl;
            cerr << endl;
            continue;
        }

        if (!english.contains(first) || !english.contains(second)) {
            cerr << "The two words must be found in the dictionary." << endl;
            cerr << endl;
            continue;
        }

        if (first == second) {
            cerr << "The two words must be different." << endl;
            cerr << endl;
            continue;
        }

        Queue<Stack<string>> stackQueue;
        Stack<string> wordLLadder;
        wordLLadder.add(first);
        stackQueue.enqueue(wordLLadder);

        Set<string> usedWords;
        usedWords.add(first);
        Stack<string> shortestLadder;

        while (!stackQueue.isEmpty()) {
            Stack<string> ladder = stackQueue.dequeue();
            string top = ladder.top();

            for (int i = 0, len = top.length(); i < len; i++) {
                for (const char& c: alphabet) {
                    string word = top;
                    word[i] = c;
                    if (english.contains(word) && !usedWords.contains(word)) {
                        if (word == second) {
                            shortestLadder = ladder;
                            goto done;
                        } else {
                            Stack<string> copy = clone(ladder);
                            copy.add(word);
                            usedWords.add(word); // avoid loop ladder
                            stackQueue.enqueue(copy);
                        }
                    }
                }
            }
        }

        done:
        if (shortestLadder.isEmpty()) {
            printNoResult(first, second);
        } else {
            shortestLadder.add(second);
            printResult(shortestLadder, first, second);
        }
    }

    cout << "Have a nice day." << endl;
    return 0;
}

void introduction() {
    cout << "Welcome to CS 106B Word Ladder. " << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
}

void printResult(Stack<string> &result, string &first, string &second) {
    cout << "A ladder from " << first << " to " << second << ":" << endl;
    while (!result.isEmpty()) {
        cout << result.pop() << " ";
    }
    cout << endl;
}

void printNoResult(string &first, string &second) {
    cout << "No word ladder found from " << first << " back to " << second << endl;
    cout << endl;
}

Stack<string>& clone(Stack<string> origin) {
    return origin;
}

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
#include "map.h"
#include "vector.h"
#include "set.h"
#include <random>

using namespace std;

void introduction();

int main() {

    introduction();

    ifstream file;
    promptUserForFile(file, "Input file name?", "File not found");

    int n;
    while (true) {
         n = getInteger("Value of N?");
         if (n >= 2)
             break;
         else
            cerr << "N must be 2 or greater." << endl;
    }

    Map<Vector<string>, Vector<string>> ngrams;
    string word;

    // construct the first n-words
    Vector<string> window;
    for (int i = 0; i < n; i++) {
        file >> word;
        window.insert(i, word);
    }
\
    // constructing the ngram
    while (file >> word) {
        // add next word to ngrams
        Vector<string> value = ngrams.get(window);
        value.add(word);
        ngrams.put(window, value);

        // advance window
        window = window.subList(1, n - 1);
        window.insert(n - 1, word);
    }

    // generate random text
    Vector<Vector<string>> keys = ngrams.keys();
    while(true) {
        int numberOfWords = getInteger("# of random words to generate (0 to quit)?");
        if (numberOfWords <= 0)
            break;
        if (numberOfWords <= n) {
            cerr << "Must be at least " << n << " words" << endl;
            continue;
        }

        int random = rand() % keys.size();
        while (true) {
            window = keys.get(random);
            // make sure that window is valid
            if (!ngrams.get(window).isEmpty())
                break;
        }

        // print the first window
        cout << "...";
        for (string w: window) {
            cout << w << " ";
        }

        // remember the last window
        Vector<string> lastWindow = window;

        // slide window
        int i = 0;
        while (i < numberOfWords - n) {
            Vector<string> value = ngrams.get(window);

            if (value.isEmpty()) {
                // if window is invalued, reset the the lastest window
                window = lastWindow;
                value = ngrams.get(window);
            }
            random = rand() % value.size();

            string suffix = value.get(random);
            cout << suffix << " ";

            // advance window
            lastWindow = window;
            window = window.subList(1, n - 1);
            window.insert(n - 1, suffix);

            i++;
        }

        cout << "..." << endl;

    }

    cout << "Exiting." << endl;
    return 0;
}

void introduction() {
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl;
    cout << "This program makes random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you. " << endl;
}

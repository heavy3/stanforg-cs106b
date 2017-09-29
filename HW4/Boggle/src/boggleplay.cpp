// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include "simpio.h"
#include "console.h"
#include <algorithm>

using namespace std;

void playOneGame(Lexicon& dictionary) {

    // TODO: implement
    string text;
    if (getYesOrNo("Do you want to generate a random board?")) {
       text = "";
    } else {
        while (true) {
            text = getLine("Type the 16 letters to appear on the board:");

            // check for invalid char (not alpha)
            bool validText = true;
            for (char c: text) {
                if (!isalpha(c)) {
                    validText = false;
                    break;
                }
            }

            if (validText && text.length() == 16)
                break;

            cerr << "That is not a valid 16-letter board string. Try again." << endl;
        }


    }
    Boggle boggle = Boggle(dictionary, text);

    string lastWord;
    bool validWord = false;
    string message = "It's your turn";

    // human play
    while (true) {
        clearConsole();

        // print message
        if (validWord)
            cout << "You found a new word! \"" << uppercase << lastWord << "\"" << endl;
        else
            cout << message << endl;

        // print the board
        cout << boggle << endl;

        // print gameplay
        cout << "Your words (" << boggle.numberOfFoundWords() << ")" << boggle.foundWordsString() << endl;
        cout << "Your scores: " << boggle.getScoreHuman() << endl;
        string word = getLine("Type a word (or Enter to stop):");

        // quit
        if (word.empty())
            break;

        // upper case all word before processing
        word = toUpperCase(word);

        if (boggle.checkWord(word)) {
            if (boggle.humanWordSearch(word)) {
                lastWord = word;
                validWord = true;
            } else {
                message = "That word can't be formed on this board.";
                validWord = false;
            }
        } else {
            message = "You must enter an unfound 4+ letter word from the dictionary.";
            validWord = false;
        }
    }

    cout << endl;

    // computer play
    cout << "It's my turn!" << endl;
    Set<string> totalWords = boggle.computerWordSearch();
    cout << "My words (" << boggle.totalWords() << "): " << totalWords.toString() << endl;
    cout << "My score: " << boggle.getScoreComputer() << endl;

    // result
    if (boggle.getScoreHuman() > boggle.getScoreComputer())
        cout << "WOW, you defeated me! Congratulations!" << endl;
    else
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl; // assume that computer always beat human :)
}

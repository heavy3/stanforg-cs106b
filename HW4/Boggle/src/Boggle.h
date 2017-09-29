// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

    // my function
    int numberOfFoundWords();
    string foundWordsString();
    int totalWords();
    string totalWordsString();

private:
    // TODO: add any other member functions/variables necessary
    Lexicon dictionary;

    Grid<char> board;
    Grid<bool> visited;

    Set<string> humanFoundWords;
    int humanScore;

    Set<string> machineFoundWords;
    int machineScores;

    // recurisvely find neighbor for cell at row r, col c for the remaining letter
    bool findNeighbor(int r, int c, string remain);
    void exploreNeighbor(int r, int c, string soFar);
};

#endif // _boggle_h

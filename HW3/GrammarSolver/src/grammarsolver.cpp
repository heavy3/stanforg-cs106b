/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "map.h"
#include "random.h"

using namespace std;

// parse input stream and construct a data structure
Map<string, Vector<Vector<string>>> parseInput(istream& input);

// construct random string base on symbol
void generateString(const Map<string, Vector<Vector<string>>>& bnf, string symbol, Vector<string>& words);

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function

    // parse input file
    const Map<string, Vector<Vector<string>>> bnf = parseInput(input);

    // generate random string
    Vector<string> results;
    for (int i = 0; i < times; i++) {
        Vector<string> words;
        generateString(bnf, symbol, words);
        results.add(stringJoin(words.toStlVector(), " "));
    }

    return results;           // This is only here so it will compile
}

Map<string, Vector<Vector<string>>> parseInput(istream& input) {
    string word;
    // init bnf in stack, if we return by reference, the stack will be deallocated and then return the empty map
    Map<string, Vector<Vector<string>>> bnf;

    while(getline(input, word)) {
        Vector<string> grammar = stringSplit(word, "::=");
        Vector<string> rules = stringSplit(grammar[1], "|");
        Vector<Vector<string>> mapRules;
        for (string rule: rules) {
            Vector<string> termials = stringSplit(rule, " ");
            mapRules.add(termials);
        }
        bnf.add(grammar[0], mapRules);
    }

    return bnf;
}

void generateString(const Map<string, Vector<Vector<string>>>& bnf, string symbol, Vector<string>& words) {
    Vector<Vector<string>> grammar = bnf.get(symbol);
    if (grammar.size() == 0) {
        // the symbol is the vocab in this bnf
        words.add(symbol);
    } else {
        int ruleIndex = randomInteger(0, grammar.size() - 1);
        Vector<string> rule = grammar.get(ruleIndex);
        for (string terminal: rule) {
            generateString(bnf, terminal, words);
        }
    }
}

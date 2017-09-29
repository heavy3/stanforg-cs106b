// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText): board(4, 4), humanFoundWords(), humanScore(0), machineFoundWords(), machineScores(0), visited(4, 4) {
    // TODO: implement
    this->dictionary = dictionary;
    if (boardText.empty()) {
        Vector<int> cubeIndex(16);
        for (int i = 0, len = cubeIndex.size(); i < len; i++) {
            cubeIndex[i] = i;
        }
        shuffle(cubeIndex);

        for (int i: cubeIndex) {
            int sideIndex = randomInteger(0, 5);
            int r = i / 4;
            int c = i % 4;
            board[r][c] = CUBES[i][sideIndex];
        }

    } else {
        boardText = toUpperCase(boardText);
        // assume that boardText is in proper form
        for (int i = 0; i < 16; i++) {
            int r = i / 4;
            int c = i % 4;
            board[r][c] = boardText[i];
            visited[r][c] = false;
        }
    }
}

char Boggle::getLetter(int row, int col) {
    // TODO: implement
    if (row >= board.numRows() || col >= board.numCols() || row < 0 || col < 0)
        throw invalid_argument("board index out of bounds");
    return board[row][col];
}

bool Boggle::checkWord(string word) {
    // TODO: implement
    return word.length() >= 4
            && dictionary.contains(word)
            && !humanFoundWords.contains(word);
}

bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    bool found = false;
    for (int r = 0; r < board.numRows(); r++) {
        for (int c = 0; c < board.numCols(); c++) {
            visited[r][c] = true;
            if (findNeighbor(r, c, word)) {
                humanFoundWords.add(word);
                found = true;
                humanScore += word.size() - 3;
                visited[r][c] = false;
                goto end;
            }
            visited[r][c] = false;
        }
    }

    end:
    return found;   // remove this
}

int Boggle::getScoreHuman() {
    // TODO: implement
    return humanScore;
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    for (int r = 0; r < board.numRows(); r++) {
        for (int c = 0; c < board.numCols(); c++) {
            exploreNeighbor(r, c, "");
        }
    }
    return machineFoundWords;
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return machineScores;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    int numRols = boggle.board.numRows();
    int numCols = boggle.board.numCols();
    for (int r = 0; r < numRols; r++) {
        for (int c = 0; c < numCols; c++) {
            out << boggle.getLetter(r, c);
        }
        out << endl;
    }
    return out;
}

int Boggle::numberOfFoundWords() {
    return humanFoundWords.size();
}

string Boggle::foundWordsString() {
    return humanFoundWords.toString();
}

int Boggle::totalWords() {
    return machineFoundWords.size();
}

bool Boggle::findNeighbor(int r, int c, string remain) {
    if (r < 0 || c < 0 || r >= board.numRows() || c >= board.numCols()) {
        // out of range neighbor
        return false;
    } else if (remain.length() <= 1) {
        // last word
        return remain[0] == board[r][c];
    } else if (board[r][c] != remain[0]) {
        // stop as soon as the word is not valid
        return false;
    } else {
        remain = remain.substr(1);
        return findNeighbor(r - 1, c - 1, remain)   // top left
               || findNeighbor(r - 1, c, remain)    // top
               || findNeighbor(r - 1, c + 1, remain)//top right
               || findNeighbor(r, c + 1, remain)    // right
               || findNeighbor(r + 1, c + 1, remain)// bottom right
               || findNeighbor(r + 1, c, remain)    // bottom
               || findNeighbor(r + 1, c - 1, remain)// bottom left
               || findNeighbor(r, c - 1, remain);   // left
    }
}

void Boggle::exploreNeighbor(int r, int c, string soFar) {
    if (r < 0 || c < 0 || r >= board.numRows() || c >= board.numCols()) {
        // return if we get out of bounds
        return;
    } if (visited[r][c]) {
        // return if this cell has been visited
        return;
    } else {
        // update and check if the word is in dictionary
        soFar += board[r][c];

        if (!dictionary.containsPrefix(soFar)) {
            // return as fast as there is no posible word
            return;
        }

        if (soFar.length() >= 4 && dictionary.contains(soFar)
                && !humanFoundWords.contains(soFar) && !machineFoundWords.contains(soFar)) {
            machineFoundWords.add(soFar);
            machineScores += soFar.size() - 3;
        }

        // choose, remember to choose here, not too early :)
        visited[r][c] = true;

        exploreNeighbor(r - 1, c -1, soFar); // top left
        exploreNeighbor(r - 1, c, soFar);    // top
        exploreNeighbor(r - 1, c + 1, soFar);// top right
        exploreNeighbor(r, c + 1, soFar);    // right
        exploreNeighbor(r + 1, c + 1, soFar);// bottom right
        exploreNeighbor(r + 1, c, soFar);    // bottom
        exploreNeighbor(r + 1, c - 1, soFar);// bottom left
        exploreNeighbor(r, c - 1, soFar);    // left

        // un-choose
        visited[r][c] = false;
    }
}

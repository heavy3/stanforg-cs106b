// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "mymap.h"
#include "pqueue.h"
// TODO: include any other headers you need
#include "filelib.h"

MyMap buildFrequencyTable(istream& input) {
    // TODO: implement this function
    MyMap freqTable;   // this is just a placeholder so it will compile

    while (!input.eof()) {
        int c = input.get();

        // put stanford eof char
        if (c == -1) {
            freqTable.put(PSEUDO_EOF, 1);
            break;
        }

        // put char in frequency table
        if (freqTable.containsKey(c))
            freqTable.put(c, freqTable.get(c) + 1);
        else
            freqTable.put(c, 1);
    }

    return freqTable;          // this is just a placeholder so it will compile
}

HuffmanNode* buildEncodingTree(const MyMap& freqTable) {
    PriorityQueue<HuffmanNode*> queue;
    Vector<int> keys = freqTable.keys();
    for (int key: keys) {
        int priority = freqTable.get(key);
        HuffmanNode* node = new HuffmanNode(key, priority);
        queue.enqueue(node, priority);
    }

    while (queue.size() > 1) {
        HuffmanNode* left = queue.dequeue();
        HuffmanNode* right = queue.dequeue();
        int priority = left->count + right->count;
        HuffmanNode* parent = new HuffmanNode(NOT_A_CHAR, priority, left, right);
        queue.enqueue(parent, priority);
    }

    return queue.dequeue();   // this is just a placeholder so it will compile
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile

    if (!encodingTree->isLeaf()) {
        // may the tree not empty
        buildEncodingMap(encodingTree->zero, "0", encodingMap);
        buildEncodingMap(encodingTree->one, "1", encodingMap);
    }

    return encodingMap;             // this is just a placeholder so it will compile
}

// encoding recursively
void buildEncodingMap(HuffmanNode* node, string soFar, Map<int, string>& encode) {
    if (node->isLeaf()) {
        encode.add(node->character, soFar);
        return;
    } else if (node == nullptr) {
        return;
    } else {
        buildEncodingMap(node->zero, soFar + "0", encode);
        buildEncodingMap(node->one, soFar + "1", encode);
    }
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
    while (!input.eof()) {
        char c = input.get();
        string encode;
        if (c == - 1) {
            encode = encodingMap.get(PSEUDO_EOF);
        } else {
            encode = encodingMap.get(c);
        }

        while (!encode.empty()) {
            int bit = stringToInteger(encode.substr(0, 1));
            output.writeBit(bit);
            encode = encode.substr(1);
        }
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
    decodeData(input, encodingTree, encodingTree, output);
}

void decodeData(ibitstream& input, HuffmanNode* root, HuffmanNode* current, ostream& output) {
     if (current->isLeaf()) {
        if (current->character == PSEUDO_EOF) {
            return;
        } else {
            output.put(current->character);
            decodeData(input, root, root, output);
        }
    } else if (input.eof()) {
        return;
    } else {
        int bit = input.readBit();
        if (bit == 0) {
            decodeData(input, root, current->zero, output);
        } else {
            decodeData(input, root, current->one, output);
        }
    }
}


void compress(istream& input, obitstream& output) {
    // TODO: implement this function
    MyMap freqTable = buildFrequencyTable(input);
    HuffmanNode* huffmanTree = buildEncodingTree(freqTable);
    Map<int, string> encodingMap = buildEncodingMap(huffmanTree);
    output << freqTable;
    rewindStream(input);
    encodeData(input, encodingMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
    MyMap freqTable;
    input >> freqTable;
    HuffmanNode* huffmanTree = buildEncodingTree(freqTable);
    decodeData(input, huffmanTree, output);
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
    if (node == nullptr) {
        return;
    } else if (node->isLeaf()) {
        delete node;
    } else {
        freeTree(node->zero);
        freeTree(node->one);
    }
}

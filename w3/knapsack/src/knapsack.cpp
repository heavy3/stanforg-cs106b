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

struct object {
    int weight;
    int value;
};

void introduction();
int fillSnapsack(Vector<object> &objects, int targetWeight);
int fillSnapsack(Vector<object> &objects, int weight, int bestScores);

int main() {

    introduction();

    while (true) {
        int numberOfObject = getInteger("Number of object: ");

        if (numberOfObject <= 0) {
            cerr << "Number of object must > 0" << endl;
            continue;
        }

        Vector<object> objects;
        for (int i = 0; i < numberOfObject; i++) {
            object obj;
            obj.value = getInteger("Object value: ");
            obj.weight = getInteger("Object weight: ");
            objects.add(obj);
        }

        int targetWeight = getInteger("Target weight: ");

//        Set<object> best;
        int bestScores = fillSnapsack(objects, targetWeight);

        cout << "Best scores is " << bestScores << " with objects: " << endl;
//        for (object obj:  best) {
//            cout << "Weight " << obj.weight << " value " << obj.value << endl;
//        }
    }

    return 0;
}

void introduction() {
    cout << "Knapsack solving" << endl;
}

int fillSnapsack(Vector<object> &objects, int targetWeight) {
    return fillSnapsack(objects, targetWeight, 0);
}

int fillSnapsack(Vector<object> &objects, int weight, int bestScores) {
    if (weight < 0)
        // if weight < 0, it's invalid so return 0 to not count this item
        return 0;

    int localBestScores = bestScores;

    for (int i = 0, len = objects.size(); i < len; i++) {
        object obj = objects[i];
        int currValue = bestScores + obj.value;
        int currWeight = weight - obj.weight;

        // remove obj for recursion
        objects.remove(i);
        currValue = fillSnapsack(objects, currWeight, currValue);
        if (localBestScores < currValue) {
            // get the best item that add the most value each iteration
            localBestScores = currValue;
//            best.add(obj);
        }

        // readd
        objects.insert(i, obj);
    }
    return localBestScores;
}

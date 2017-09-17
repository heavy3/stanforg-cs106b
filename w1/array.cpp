#include <iostream>
#include "console.h"
#include "vector.h"

using namespace std;

const int NUM_ELEMENTS = 100000;

int main() {
    // std::cout << "Hello, world" << std::endl;
    Vector<int> myList;
    cout << "Populating a vector with even integers less than " << (NUM_ELEMENTS * 2) << endl;

    for (int i = 0; i < NUM_ELEMENTS; i++ {
        myList.add(i*2);
    }

    for (int i : myList) {
        cout << i << endl;
    }
    return 0
}
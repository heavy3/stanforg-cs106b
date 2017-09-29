#include <iostream>

using namespace std;

void printBinary(int n);
void intro();

int main() {
    intro();

    int number;
    do {
        cout << "Enter an integer (-1 to exist): ";
        cin >> number;
        printBinary(number);
        cout << endl;
    } while (number != -1);

    return 0;
}

void intro() {
    cout << "A prgram to convert integer from dec to bi" << endl;
}

void printBinary(int n) {
    if (n < 2) {
        cout << n;
    } else {
        printBinary(n / 2);
        printBinary( n % 2);
    }
}
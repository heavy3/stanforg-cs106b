#include <iostream>

using namespace std;

void intro();
void nameDiamond(string &name);

int main() {
    intro();

    string name;
    while (true) {
        cout << "Enter string: ";
        cin >> name;
        nameDiamond(name);
    }

    return 0;
}

void intro() {
    cout << "Print string in diamond format" << endl;
}

void nameDiamond(string &name) {
    string diamond;
    int len = name.length();

    // print top of the diamond
    for (int i = 0; i < len; i++) {
        diamond += name[i];
        cout << diamond << endl;
    }

    // print the bottom part
    for (int i = 0; i < len; i++) {
        diamond[i] = ' ';
        cout << diamond << endl;
    }

}
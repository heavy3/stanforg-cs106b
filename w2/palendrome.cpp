#include <iostream>

using namespace std;

bool isPalindrome(const string &s);
void intro();

int main() {
    intro();

    string word;
    do {
        cout << "Enter a word (blank to exist): ";
        getline(cin, word);
        bool answer = isPalindrome(word);
        cout << "Palindrome " << (answer ? "True": "False") << endl;
    } while (word != "");

    return 0;
}

void intro() {
    cout << "A prgram to check if a word is palendrome or not" << endl;
}

bool isPalindrome(const string &s) {
    if (s.length() < 2)
        return true;
    else if (s[0] != s[s.length() - 1])
        return false;
    else {
        string middle = s.substr(1, s.length() - 2);
        return isPalindrome(middle);
    }    
    
}
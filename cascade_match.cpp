//
// Created by azra on 6.02.2025.
//


#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string filename;
    cout << "Please enter the file name: ";
    cin >> filename;

    ifstream input;
    input.open(filename);

    while (input.fail()) {
        cout << "The file couldn't be opened." << endl;
        cout << "Please enter a valid file name: ";
        cin >> filename;
        input.open(filename);
    }

    //cout << "Successfully opened.";

    string line;

    return 0;
}

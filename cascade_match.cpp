//
// Created by azra on 6.02.2025.
//


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<char>> readMatrixFromFile(ifstream& input) {
    string line;
    vector <vector<char>> mat;
    int i = 0;

    //Fill the matrix from the txt file
    while (!input.eof()) {
        getline(input, line);
        vector <char> row;
        for (int j = 0; j < line.length(); j ++) {
            row.push_back(line[j]);
        }
        mat.push_back(row);
        i++;
    }

    return mat;
}

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

    vector<vector<char>> matrix = readMatrixFromFile(input);

    return 0;
}


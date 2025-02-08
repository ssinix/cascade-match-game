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
        for (char c : line) {
            row.push_back(c);
        }
        mat.push_back(row);
        i++;
    }

    return mat;
}

bool validMatrix(const vector<vector<char>>& mat) {
    int rowLength = mat[0].size();

    for (const vector<char>& row : mat) {
        if (row.size() != rowLength)
            return false;;

        for (char c : row) {
            if (!(c == 'X' || c == 'O' || c == 'S'))
                return false;
        }
    }
    return true;
}

bool validMove(int row_idx, int col_idx, char dir, const vector<vector<char>>& mat) {
    if (!(dir == 'r' || dir == 'l' || dir == 'u' || dir == 'd')) {
        cout << "Invalid input. Try again." << endl;
        return false;
    }
    if (row_idx > mat.size() || col_idx > mat[0].size()) {
        cout << "Invalid coordinates!" << endl;
    }



}

int main() {
    string filename;
    cout << "Please enter the file name:" << endl;
    cin >> filename;

    ifstream input;
    input.open(filename);

    while (input.fail()) {
        cout << "The file couldn't be opened." << endl;
        cout << "Please enter a valid file name:" << endl;
        cin >> filename;
        input.open(filename);
    }
    //cout << "Successfully opened.";

    vector<vector<char>> matrix = readMatrixFromFile(input);
    input.close();

    if (!validMatrix(matrix)) {
        cout << "The matrix either has invalid dimensions or contains invalid characters."<< endl;
        cout << "Exiting the game. Bye bye.";
        return 0;
    }

    cout << "The content of the matrix is:" << endl;
    for (const vector<char>& row : matrix) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }

    int row_idx, col_idx;
    char direction;
    cout << "Enter row, col, and direction (r/l/u/d). Type '0 0 q' to exit." << endl << "Move:" << endl;
    cin >> row_idx >> col_idx >> direction;

    while (!(row_idx == 0 && col_idx == 0 && direction == 'q')) {

    }

    return 0;
}


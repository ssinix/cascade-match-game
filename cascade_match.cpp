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

void printMatrix(const vector<vector<char>>& mat) {
    for (const vector<char>& row : mat) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}

void swapCells(int row_idx, int col_idx, char dir,vector<vector<char>>& mat) {
    char temp = mat[row_idx][col_idx];
    if (dir == 'l') {
        mat[row_idx][col_idx] = mat[row_idx][col_idx - 1];
        mat[row_idx][col_idx - 1] = temp;
    }
    else if (dir == 'r') {
        mat[row_idx][col_idx] = mat[row_idx][col_idx + 1];
        mat[row_idx][col_idx + 1] = temp;
    }
    else if (dir == 'u') {
        mat[row_idx][col_idx] = mat[row_idx - 1][col_idx];
        mat[row_idx - 1][col_idx] = temp;
    }
    else if (dir == 'd') {
        mat[row_idx][col_idx] = mat[row_idx + 1][col_idx];
        mat[row_idx + 1][col_idx] = temp;
    }
}

bool validMove(int row_idx, int col_idx, char dir, const vector<vector<char>>& mat) {
    if (!(dir == 'r' || dir == 'l' || dir == 'u' || dir == 'd' || dir == 'q')) {
        cout << "Invalid input. Try again." << endl;
        return false;
    }
    if (row_idx > mat.size() - 1 || col_idx > mat[0].size() - 1 || row_idx < 0 || col_idx < 0) {
        cout << "Invalid coordinates!" << endl;
        return false;
    }
    if ((col_idx == 0 && dir == 'l') || (col_idx == mat[0].size() - 1 && dir == 'r') || (row_idx == 0 && dir == 'u') || (row_idx == mat.size() - 1 && dir == 'd')) {
        cout << "Move out of bounds!" << endl;
        return false;
    }



    return true;
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
    printMatrix(matrix);

    int row_idx, col_idx;
    char direction;
    cout << "Enter row, col, and direction (r/l/u/d). Type '0 0 q' to exit." << endl << "Move:" << endl;
    cin >> row_idx >> col_idx >> direction;

    while (!(row_idx == 0 && col_idx == 0 && direction == 'q')) {
        while (!validMove(row_idx,col_idx,direction,matrix)) {
            cout << "Move:" << endl;
            cin >> row_idx >> col_idx >> direction;
        }

        cout << "Move:" << endl;
        cin >> row_idx >> col_idx >> direction;
    }

    return 0;
}


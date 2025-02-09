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

    // Fill the matrix from the txt file
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

bool clearMatches(vector<vector<char>>& mat, vector<int>& match_rows, vector<int>& match_cols) {
    bool match = false;
    // Check for row matches (horizontal)
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size() - 2; j++) {  // Check 3 at a time
            if (mat[i][j] != '-' && mat[i][j] == mat[i][j + 1] && mat[i][j] == mat[i][j + 2]) {
                match = true;
                int k = j;
                while (k < mat[0].size() && mat[i][k] == mat[i][j]) {
                    match_rows.push_back(i); // Store row index
                    match_cols.push_back(k); // Store column index
                    k++;
                }
                j = k; // Move past the matched segment
            }
        }
    }
    for (int idx = 0; idx < match_rows.size(); idx++) {
        mat[match_rows[idx]][match_cols[idx]] = '-';
    }
    // Check for column matches (vertical)
    for (int j = 0; j < mat[0].size(); j++) {
        for (int i = 0; i < mat.size() - 2; i++) {  // Check 3 at a time
            if (mat[i][j] != '-' && mat[i][j] == mat[i + 1][j] && mat[i][j] == mat[i + 2][j]) {
                match = true;
                int k = i;
                while (k < mat.size() && mat[k][j] == mat[i][j]) {
                    match_rows.push_back(k); // Store row index
                    match_cols.push_back(j); // Store column index
                    k++;
                }
                i = k; // Move past the matched segment
            }
        }
    }
    for (int idx = 0; idx < match_rows.size(); idx++) {
        mat[match_rows[idx]][match_cols[idx]] = '-';
    }
    return match;
}

bool validMove(int row_idx, int col_idx, char dir, vector<vector<char>>& mat, vector<int>& match_rows, vector<int>& match_cols, vector<vector<char>>& swapped_vector) {
    if (row_idx == 0 && col_idx == 0 && dir == 'q') {
        return false;
    }
    if (!(dir == 'r' || dir == 'l' || dir == 'u' || dir == 'd' || dir == 'q')) {
        cout << "Invalid input. Try again." << endl;
        return false;
    }
    if (row_idx < 0 || col_idx < 0) {
        cout << "Invalid input. Try again." << endl;
        return false;
    }
    if (row_idx > mat.size() - 1 || col_idx > mat[0].size() - 1) {
        cout << "Invalid coordinates!" << endl;
        return false;
    }
    if ((col_idx == 0 && dir == 'l') || (col_idx == mat[0].size() - 1 && dir == 'r') || (row_idx == 0 && dir == 'u') || (row_idx == mat.size() - 1 && dir == 'd')) {
        cout << "Move out of bounds!" << endl;
        return false;
    }
    if ((dir == 'l' && mat[row_idx][col_idx - 1] == '-') || (dir == 'r' && mat[row_idx][col_idx + 1] == '-') || (dir == 'u' && mat[row_idx - 1][col_idx] == '-') || (dir == 'd' && mat[row_idx + 1][col_idx] == '-') || mat[row_idx][col_idx] == '-' && dir != 'q') {
        cout << "Cannot swap with an empty cell!" << endl;
        return false;
    }
    swapCells(row_idx,col_idx,dir,mat);
    swapped_vector = mat;
    if (!clearMatches(swapped_vector,match_rows,match_cols) && dir != 'q') {
        cout << "Invalid move: No match found!" << endl;
        swapCells(row_idx,col_idx,dir,mat);
        swapped_vector.clear();
        return false;
    }
    return true;
}

void applyGravity(vector<vector<char>>& mat) {
    for (int j = 0; j < mat[0].size(); j++) {
        for (int i = mat.size() - 2; i >= 0; i--) {
            int k = i;
            while (k < mat.size() - 1 && mat[k+1][j] == '-') {
                mat[k+1][j] = mat[k][j];
                mat[k][j] = '-';
                k++;
            }
        }
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
    printMatrix(matrix);

    int row_idx, col_idx;
    char direction;
    cout << "\nEnter row, col, and direction (r/l/u/d). Type '0 0 q' to exit." << endl << "Move:" << endl;
    cin >> row_idx >> col_idx >> direction;

    vector<int> match_rows, match_cols;
    vector<vector<char>> cleared_matrix;

    while (!(row_idx == 0 && col_idx == 0 && direction == 'q')) {
        while (!validMove(row_idx,col_idx,direction,matrix,match_rows,match_cols, cleared_matrix)) {
            if (row_idx == 0 && col_idx == 0 && direction == 'q') {
                cout << "Exiting the game. Bye bye.";
                return 0;
            }
            cout << "Move:" << endl;
            cin >> row_idx >> col_idx >> direction;
        }

        cout << "After swap:" << endl;
        printMatrix(matrix);

        cout << "\nMove successful. Clearing matches..." << endl;
        cout << "After clearing matches:" << endl;
        // Already cleared when checking move validity
        printMatrix(cleared_matrix);
        // Clear previous matches before next move
        match_rows.clear();
        match_cols.clear();

        cout << "\nAfter applying gravity:" << endl;
        applyGravity(cleared_matrix);
        printMatrix(cleared_matrix);
        // Update matrix with cleared matrix
        matrix = cleared_matrix;

        cout << "\nMove:" << endl;
        cin >> row_idx >> col_idx >> direction;
    }

    cout << "Exiting the game. Bye bye.";
    return 0;
}


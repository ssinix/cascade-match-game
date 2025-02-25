//
// Created by azra on 6.02.2025.
//


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Reads the matrix from input file and returns if the matrix is valid or not
bool readValidMatrix(ifstream& input, vector<vector<char>>& mat) {
    string line;
    int i = 0;
    bool valid = true;

    // Fill the matrix from the input file
    while (!input.eof()) {
        getline(input, line);
        vector <char> row;
        // Check if each character is valid
        for (char c : line) {
            if (!(c == 'X' || c == 'O' || c == 'S'))
                valid = false;
            row.push_back(c);
        }
        mat.push_back(row);
        // Check if every row is the same length
        int rowLength = mat[0].size();
        if (row.size() != rowLength)
            valid = false;
        i++;
    }
    return valid;
}

// Prints the current matrix
void printMatrix(const vector<vector<char>>& mat) {
    for (const vector<char>& row : mat) {
        for (char c : row) {
            cout << c;
        }
        cout << endl;
    }
}

// Swaps two adjacent cells according to the direction
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

// Finds and clears matches with priority to the horizontal axis
// Returns true if there are any matches found
bool clearMatches(vector<vector<char>>& mat, vector<int>& match_rows, vector<int>& match_cols) {
    bool match = false;
    // Check for row matches (horizontal)
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size() - 2; j++) {  // Check 3 at a time
            if (mat[i][j] != '-' && mat[i][j] == mat[i][j + 1] && mat[i][j] == mat[i][j + 2]) {
                match = true;
                int k = j;
                // Continue checking for a match bigger than 3
                while (k < mat[0].size() && mat[i][k] == mat[i][j]) {
                    match_rows.push_back(i); // Store row index
                    match_cols.push_back(k); // Store column index
                    k++;
                }
                j = k; // Move past the matched segment
            }
        }
    }
    // Clear matches along the horizontal axis before checking along the vertical
    for (int idx = 0; idx < match_rows.size(); idx++) {
        mat[match_rows[idx]][match_cols[idx]] = '-';
    }
    // Check for column matches (vertical)
    for (int j = 0; j < mat[0].size(); j++) {
        for (int i = 0; i < mat.size() - 2; i++) {  // Check 3 at a time
            if (mat[i][j] != '-' && mat[i][j] == mat[i + 1][j] && mat[i][j] == mat[i + 2][j]) {
                match = true;
                int k = i;
                // Continue checking for a match bigger than 3
                while (k < mat.size() && mat[k][j] == mat[i][j]) {
                    match_rows.push_back(k); // Store row index
                    match_cols.push_back(j); // Store column index
                    k++;
                }
                i = k; // Move past the matched segment
            }
        }
    }
    // Clear matches along the vertical axis
    for (int idx = 0; idx < match_rows.size(); idx++) {
        mat[match_rows[idx]][match_cols[idx]] = '-';
    }
    return match;
}

// Checks for move validity and performs it if valid
// Returns true if the move is valid
bool validMove(int row_idx, int col_idx, char dir, vector<vector<char>>& mat, vector<int>& match_rows, vector<int>& match_cols, vector<vector<char>>& swapped_vector) {
    // Check if it's the exit case
    if (row_idx == 0 && col_idx == 0 && dir == 'q') {
        return false;
    }
    // Check for valid direction character
    if (!(dir == 'r' || dir == 'l' || dir == 'u' || dir == 'd' || dir == 'q')) {
        cout << "Invalid input. Try again." << endl;
        return false;
    }
    // Check for valid coordinates -> cannot be negative
    if (row_idx < 0 || col_idx < 0) {
        cout << "Invalid input. Try again." << endl;
        return false;
    }
    // Check for valid coordinates -> cannot be outside the matrix
    if (row_idx > mat.size() - 1 || col_idx > mat[0].size() - 1) {
        cout << "Invalid coordinates!" << endl;
        return false;
    }
    // Check for valid swap -> the cell we're trying to swap with cannot be outside the matrix
    if ((col_idx == 0 && dir == 'l') || (col_idx == mat[0].size() - 1 && dir == 'r') || (row_idx == 0 && dir == 'u') || (row_idx == mat.size() - 1 && dir == 'd')) {
        cout << "Move out of bounds!" << endl;
        return false;
    }
    // Check for valid swap -> cannot swap with a cleared (empty) cell
    if ((dir == 'l' && mat[row_idx][col_idx - 1] == '-') || (dir == 'r' && mat[row_idx][col_idx + 1] == '-') || (dir == 'u' && mat[row_idx - 1][col_idx] == '-') || (dir == 'd' && mat[row_idx + 1][col_idx] == '-') || mat[row_idx][col_idx] == '-' && dir != 'q') {
        cout << "Cannot swap with an empty cell!" << endl;
        return false;
    }
    // If valid until now, swap cells and check for at least one match
    swapCells(row_idx,col_idx,dir,mat);
    swapped_vector = mat; // Store the swapped matrix in a different 2D vector
    // clearMatches function returns if there was at least one match or not and clears found matches
    if (!clearMatches(swapped_vector,match_rows,match_cols) && dir != 'q') {
        cout << "Invalid move: No match found!" << endl;
        // Since no matches found, swap back to original matrix and clear swapped vector
        swapCells(row_idx,col_idx,dir,mat);
        swapped_vector.clear();
        return false;
    }
    return true;
}

// Applies gravity to make characters above empty cells fall
void applyGravity(vector<vector<char>>& mat) {
    // Loop through each column from bottom to top
    for (int j = 0; j < mat[0].size(); j++) {
        for (int i = mat.size() - 2; i >= 0; i--) {
            int k = i;
            // Move characters down while there are empty spaces below
            while (k < mat.size() - 1 && mat[k+1][j] == '-') {
                mat[k+1][j] = mat[k][j];
                mat[k][j] = '-';
                k++;
            }
        }
    }
}

int main() {
    // Get input filename and open it
    string filename;
    cout << "Please enter the file name:" << endl;
    cin >> filename;

    ifstream input;
    input.open(filename);

    // Keep asking for valid file name until successful
    while (input.fail()) {
        cout << "The file couldn't be opened." << endl;
        cout << "Please enter a valid file name:" << endl;
        cin >> filename;
        input.open(filename);
    }
    //cout << "Successfully opened.";

    vector<vector<char>> matrix;

    // Read matrix from file and check validity
    if (!readValidMatrix(input,matrix)) {
        cout << "The matrix either has invalid dimensions or contains invalid characters."<< endl;
        cout << "Exiting the game. Bye bye.";
        return 0;
    }
    input.close();

    // Display initial matrix
    cout << "The content of the matrix is:" << endl;
    printMatrix(matrix);

    // Ask for initial move
    int row_idx, col_idx;
    char direction;
    cout << "\nEnter row, col, and direction (r/l/u/d). Type '0 0 q' to exit." << endl << "Move:" << endl;
    cin >> row_idx >> col_idx >> direction;

    vector<int> match_rows, match_cols;     // vectors to store matches
    vector<vector<char>> cleared_matrix;    // 2D vector to store matrix after clearing matches

    // Keep asking for moves until exit case '0 0 q' is entered
    while (!(row_idx == 0 && col_idx == 0 && direction == 'q')) {
        // Keep asking for moves until valid move entered
        while (!validMove(row_idx,col_idx,direction,matrix,match_rows,match_cols, cleared_matrix)) {
            if (row_idx == 0 && col_idx == 0 && direction == 'q') {
                cout << "Exiting the game. Bye bye.";
                return 0;
            }
            cout << "Move:" << endl;
            cin >> row_idx >> col_idx >> direction;
        }

        // Matrix is swapped when checking move validity
        cout << "After swap:" << endl;
        printMatrix(matrix);

        cout << "\nMove successful. Clearing matches..." << endl;
        cout << "After clearing matches:" << endl;
        // Cleared matrix is stored when checking move validity
        printMatrix(cleared_matrix);

        // Empty previous found matches before next move
        match_rows.clear();
        match_cols.clear();

        // Apply gravity on the cleared matrix
        cout << "\nAfter applying gravity:" << endl;
        applyGravity(cleared_matrix);
        printMatrix(cleared_matrix);
        // Update matrix with cleared matrix
        matrix = cleared_matrix;

        // Keep clearing matches caused by gravity until no matches found
        while (clearMatches(matrix,match_rows,match_cols)) {
            cout << "\nAfter clearing matches:" << endl;
            printMatrix(matrix);

            cout << "\nAfter applying gravity:" << endl;
            applyGravity(matrix);
            printMatrix(matrix);

            // Empty matches after every cycle
            match_rows.clear();
            match_cols.clear();
        }

        // Ask for next move
        cout << "\nMove:" << endl;
        cin >> row_idx >> col_idx >> direction;
    }

    cout << "Exiting the game. Bye bye.";
    return 0;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 10;

class Matrix {
    vector<vector<int>> data;
    int size;

public:
    Matrix(int n = 0) : size(n), data(n, vector<int>(n, 0)) {}

    // Function to load matrix data from a file
    bool loadFromFile(const string &filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open file " << filename << endl;
            return false;
        }
        
        file >> size;
        if (size <= 0 || size > MAX_SIZE) {
            cerr << "Invalid matrix size in file." << endl;
            return false;
        }
        
        data.resize(size, vector<int>(size, 0));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!(file >> data[i][j])) {
                    cerr << "Error reading matrix values from file." << endl;
                    return false;
                }
            }
        }
        file.close();
        return true;
    }

    // Function to display the matrix
    void display() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << setw(4) << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Operator for matrix addition
    Matrix operator+(const Matrix &other) const {
        Matrix result(size);
        if (size != other.size) {
            cerr << "Error: Matrix sizes do not match for addition." << endl;
            return result;
        }
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Operator for matrix multiplication
    Matrix operator*(const Matrix &other) const {
        Matrix result(size);
        if (size != other.size) {
            cerr << "Error: Matrix sizes do not match for multiplication." << endl;
            return result;
        }
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Function to get the sum of diagonal elements
    int getDiagonalSum() const {
        int mainDiagonalSum = 0, secondaryDiagonalSum = 0;
        for (int i = 0; i < size; i++) {
            mainDiagonalSum += data[i][i];           // Main diagonal
            secondaryDiagonalSum += data[i][size - i - 1]; // Secondary diagonal
        }
        return mainDiagonalSum + secondaryDiagonalSum;
    }

    // Function to swap two rows of the matrix
    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size) {
            cerr << "Error: Invalid row indices for swap." << endl;
            return;
        }
        swap(data[row1], data[row2]);
        cout << "Rows " << row1 << " and " << row2 << " swapped." << endl;
    }
};

int main() {
    Matrix matrix1, matrix2;
    string filename = "matrix_input.txt";

    // Load matrices from the file
    cout << "Loading matrices from " << filename << "..." << endl;
    if (!matrix1.loadFromFile(filename) || !matrix2.loadFromFile(filename)) {
        cerr << "Error loading matrices from file." << endl;
        return 1;
    }

    // Display both matrices
    cout << "Matrix 1:" << endl;
    matrix1.display();
    cout << "Matrix 2:" << endl;
    matrix2.display();

    // Add matrices
    cout << "Matrix 1 + Matrix 2:" << endl;
    Matrix addResult = matrix1 + matrix2;
    addResult.display();

    // Multiply matrices
    cout << "Matrix 1 * Matrix 2:" << endl;
    Matrix multiplyResult = matrix1 * matrix2;
    multiplyResult.display();

    // Diagonal sum
    cout << "Sum of main and secondary diagonals of Matrix 1: ";
    cout << matrix1.getDiagonalSum() << endl;

    // Swap rows
    int row1 = 0, row2 = 1; // Sample row indices to swap
    cout << "Swapping rows " << row1 << " and " << row2 << " in Matrix 1:" << endl;
    matrix1.swapRows(row1, row2);
    matrix1.display();

    return 0;
}

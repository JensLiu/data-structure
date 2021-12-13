#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
class SparseMatrixRecord {
public:
    int row;
    int column;
    T value;
    SparseMatrixRecord(int row, int column, T value) :
    row(row), column(column), value(value) {}
    SparseMatrixRecord() {
        row = 0;
        column = 0;
    }
};

template <typename T>
class SparseMatrix_seqList {
    int rowCount;
    int columnCount;
    int nonZeroCount;
    SparseMatrixRecord<T>* mat;

public:

    SparseMatrix_seqList(T* matrix, int row, int column) {
        toSparseMatrix(matrix, row, column);
    }

    void toSparseMatrix(T* matrix, int row, int column) {
        rowCount = row;
        columnCount = column;
        nonZeroCount = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                if (*(matrix + i * columnCount + j) != 0) {
                    nonZeroCount++;
                }
            }
        }
        mat = new SparseMatrixRecord<T>[nonZeroCount];
        this->rowCount = row;
        this->columnCount = column;
        nonZeroCount = 0;
        SparseMatrixRecord<T>* trav = mat;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                T value = *(matrix + i * columnCount + j);
                if (value != 0) {
                    SparseMatrixRecord<T> newRecord(i, j, value);
                    *trav = newRecord;
                    trav++;
                    nonZeroCount++;
                }
            }
        }
    }

    T entryAt(int row, int column) {
        if (row < rowCount && column < columnCount) {
            for (int i = 0; i < row; i++) {
                if (mat[i].row == row && mat[i].column == column) {
                    return mat[i].value;
                }
            }
            return 0;
        }
    }

    void showRecord() {
        for (int i = 0; i < nonZeroCount; i++) {
            cout << mat[i].row << " " << mat[i].column << " " << mat[i].value << endl;
        }
    }

    void printMatrix() {
        int row = 0, column = 0;
        SparseMatrixRecord<T>* trav = mat;
        while (row < rowCount && column < columnCount) {
            if (trav < mat + nonZeroCount && row * columnCount + column == trav->row * columnCount + trav->column) {
                cout << fixed << setprecision(3) << trav->value << " ";
                trav++;
            } else {
                cout << fixed << setprecision(3) << "0 ";
            }
            column++;
            if (column >= columnCount) {
                cout << endl;
                column = 0;
                row++;
            }
        }
    }

    void reverseMatrix() {
        // max index of current column (after switch is row)
        int maxIndex = 0;
        for (int i = 0; i < nonZeroCount; i++) {
            if (maxIndex < mat[i].column) {
                maxIndex = mat[i].column;
            }
            int tmp = mat[i].column;
            mat[i].column = mat[i].row;
            mat[i].row = tmp;
        }
        // before switching, rows are sorted
        // =>after: columns are sorted
        // => need to sort row
        radixSort(maxIndex);
    }

    void radixSort(int maxRowIndex) {
        int matArrSize = nonZeroCount;
        int auxArrSize = maxRowIndex + 1;

        // make temporary array to store the records after first counting sort
        SparseMatrixRecord<T>* tmp = new SparseMatrixRecord<T>[matArrSize];

        // make auxiliary array to store the index
        int* auxArr = new int[auxArrSize];
        for (int i = 0; i < auxArrSize; i++) {
            auxArr[i] = 0;
        }

        // record time of appearance of each row number
        for (int i = 0; i < matArrSize; i++) {
            auxArr[mat[i].row]++;
        }

        // convert to indices of the first appearance of duplicate row number in the record
        auxArr[auxArrSize - 1] = matArrSize - auxArr[auxArrSize - 1];
        for (int i = auxArrSize - 1; i > 0; i--) {
            auxArr[i - 1] = auxArr[i] - auxArr[i - 1];
        }

        // after placing one element, increase its index by one
        for (int i = 0; i < matArrSize; i++) {
            tmp[auxArr[mat[i].row]++] = mat[i];
        }

        delete[] mat;
        mat = tmp;
    }
};


int main() {
    int matrix[5][5] = {
            { 1, 1, 0, 5, 1 },
            { 2, 0, 1, 1, 0 },
            { 0, 0, 4, 0, 1 },
            { 0, 1, 0, 0, 0 },
            { 1, 1, 0, 0, 0,}
    };
    SparseMatrix_seqList<int> mat((int*)matrix, 5, 5);
    mat.printMatrix();
    mat.reverseMatrix();
    cout << endl;
    mat.printMatrix();
}

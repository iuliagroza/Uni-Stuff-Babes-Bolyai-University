#include "Matrix.h"
#include <exception>

using namespace std;

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
    //TODO - Implementation
    this->nr_lines = nrLines;
    this->nr_cols = nrCols;

    this->line_size = 0;
    this->line_capacity = 5;

    this->sparse_column = new int[this->nr_cols + 1]{NULL_TELEM};
    this->sparse_line = new int[this->line_capacity]{NULL_TELEM};
    this->values = new TElem[this->line_capacity]{NULL_TELEM};
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
Matrix::~Matrix() {
    delete[] this->sparse_column;
    delete[] this->sparse_line;
    delete[] this->values;
}

//BC: Theta(line_size)
//WC: Theta(line_size)
//Total: Theta(line_size)
void Matrix::resize() {
    auto new_sparse_line = new TElem[2 * this->line_capacity];
    auto new_values = new TElem[2 * this->line_capacity];

    for (int i = 0; i < this->line_size; i++) {
        new_sparse_line[i] = this->sparse_line[i];
        new_values[i] = this->values[i];
    }

    delete[] this->values;
    delete[] this->sparse_line;

    this->line_capacity *= 2;
    this->values = new_values;
    this->sparse_line = new_sparse_line;
}


//BC: Theta(line_size)
//WC: Theta(line_size)
//Total: Theta(line_size)
void Matrix::addToPosition(int position, int i, int j, TElem e) {
    if (this->line_size == this->line_capacity) {
        this->resize();
    }
    this->line_size++;

    for (int index = this->line_size - 1; index > position; index--) {
        this->sparse_line[index] = this->sparse_line[index - 1];
        this->values[index] = this->values[index - 1];
    }

    for (int index = j + 1; index < this->nr_cols + 1; index++) {
        this->sparse_column[index]++;
    }

    this->sparse_line[position] = i;
    this->values[position] = e;
}


//BC: Theta(line_size)
//WC: Theta(line_size)
//Total: Theta(line_size)
void Matrix::deleteFromPosition(int position, int j) {
    for (int index = position; index < this->line_size - 1; index++) {
        this->sparse_line[index] = this->sparse_line[index + 1];
        this->values[index] = this->values[index + 1];
    }
    this->line_size--;

    for (int index = j + 1; index < this->nr_cols + 1; index++) {
        this->sparse_column[index]--;
    }
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
int Matrix::nrLines() const {
    //TODO - Implementation
    return this->nr_lines;
}


//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
int Matrix::nrColumns() const {
    //TODO - Implementation
    return this->nr_cols;
}


//BC: Theta(1)
//WC: Theta(N), where N is the number of elements on the column j (sparse_column[j+1] - sparse_column[j])
//Total: O(N)
TElem Matrix::element(int i, int j) const {
    //TODO - Implementation
    if (i < 0 || i > this->nr_lines || j < 0 || j > this->nr_cols) {
        throw std::exception();
    }

    int start = this->sparse_column[j];
    int end = this->sparse_column[j + 1];

    while (start < end) {
        if (this->sparse_line[start] == i) {
            return this->values[start];
        }

        start++;
    }
    return NULL_TELEM;
}

//BC: Theta(1)
//WC: Theta(N), where N is the number of lines
//Total: O(N)
TElem Matrix::modify(int i, int j, TElem e) {
    //TODO - Implementation
    if (i < 0 || i > this->nr_lines || j < 0 || j > this->nr_cols) {
        throw std::exception();
    }

    int start = this->sparse_column[j];
    int end = this->sparse_column[j + 1];
    TElem old = NULL_TELEM;

    while (start < end) {
        if (this->sparse_line[start] == i) {
            old = this->values[start];
            if (e != NULL_TELEM) {
                this->values[start] = e;
            } else {
                this->deleteFromPosition(start, j);
            }

            return old;
        }

        if (this->sparse_line[start] > i) {
            old = this->values[start];

            this->addToPosition(start, i, j, e);

            return old;
        }

        start++;
    }

    this->addToPosition(start, i, j, e);
    return NULL_TELEM;
}

//BC: Theta(1)
//WC: Theta(1)
//Total: Theta(1)
int Matrix::numberOfNonZeroElems(int col) const {
    if(col < 0 || col > this->nr_cols) {
        throw std::exception();
    }

    return (this->sparse_column[col+1] - this->sparse_column[col]);
}
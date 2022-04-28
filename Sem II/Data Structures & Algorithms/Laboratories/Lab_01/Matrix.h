#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    //TODO - Representation
    int nr_lines;
    int nr_cols;

    int line_size;
    int line_capacity;

    int *sparse_column;
    int *sparse_line;
    TElem *values;

    //resizes the dynamic array
    void resize();

    //adds an element on the (i, j) position of the matrix
    //position indicates the position of e in the values array
    void addToPosition(int position, int i, int j, TElem e);

    //removes the element having the column j and the position position in the values array
    void deleteFromPosition(int position, int j);

public:
    //constructor
    Matrix(int nrLines, int nrCols);

    //deconstructor
    ~Matrix();

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    //returns the number of non-zero elements from a given column
    //throws an exception if col is not valid
    int numberOfNonZeroElems(int col) const;
};

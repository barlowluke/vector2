//include/matrix.hpp
#pragma once

#include "vector.hpp"
#include <stdexcept>  // std::out_of_range

namespace dsa{

class Matrix {
private:
    int rows{0};
    int cols{0};
    dsa::Vector<dsa::Vector<int>> data;

public:
    /*
    if r < 0 OR c < 0 
        throw std::out_of_range("Negative dimensions");
    rows = r
    cols = c
    for i from 0 to rows-1
        declare row vector of ints
        for j from 0 to cols-1
            append 0 to row  // initialize each element with 0
        append row to data
    */
    Matrix(int r, int c) {
        if (r < 0 || c < 0) {
            throw std::out_of_range("Negative dimensions");
        }
        int rows = r;
        int cols = c;
        for (int i = 0; i < rows - 1; i++) {
            dsa::Vector<int> row_vec;
            for (int j = 0; j < cols - 1; j++) {
                row_vec[j] = 0;
            }
            data[i] = row_vec;
        }
    }

    //data.at(i).at(j)
    int& operator()(int i, int j) {
        return data.at(i).at(j);
    }

    // throw std::out_of_range("dimensions must match")
    // result(i, j) = (*this)(i, j) + other(i, j)
    Matrix operator+(Matrix& other) {
        if (this->rows != other.rows || this->cols != other.cols) {
            throw std::out_of_range("Dimensions must match");
        }
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                result[i][j] = *this[i][j] + other[i][j];
            }
        }
        return result; // think why - ans for chaining
    }

};

}

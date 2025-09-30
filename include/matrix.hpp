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
    Matrix(int r, int c){
        // ToDo
    }

    //data.at(i).at(j)
    int& operator()(int i, int j) {
        // ToDo
    }

    // throw std::out_of_range("dimensions must match")
    // result(i, j) = (*this)(i, j) + other(i, j)
    Matrix operator+(Matrix& other) {
        // ToDo
        return result; // think why - ans for chaining
    }

};

}
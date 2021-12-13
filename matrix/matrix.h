//
// Created by Max on 12.12.2021.
//

#ifndef CIRCUIT_SOLVER_MATRIX_H
#define CIRCUIT_SOLVER_MATRIX_H

#include <utility>

#include "../includes/includes.h"

using namespace std;

class matrix {
public:
    // Constructors
    matrix(unsigned long size1_, unsigned long size2_,
           string name_ = "noname");

    matrix(vector<vector<double>> &data_, string name_ = "noname");

    matrix() = default;

    ~matrix() = default;

    // Methods
    void print_data();

    matrix transpose();

    matrix multiply(matrix &m);

    matrix inverse();

    void swap_columns(unsigned int column_n1, unsigned int column_n2);

    void addition_of_lines(unsigned int line_n1, unsigned int line_n2,
                           double coeff = 1);

    void rename(const string &name_) {
        name = name_;
    }

    // Operators
    matrix operator-();

    friend matrix operator+(matrix &lhs, matrix &rhs);

    friend matrix operator*(matrix &lhs, matrix &rhs);

    friend matrix operator*(matrix &&lhs, matrix &rhs);

    friend matrix operator*(matrix &&lhs, matrix &&rhs);

    friend matrix operator*(matrix &lhs, matrix &&rhs);


    // Data
    string name{"noname"};

    vector<vector<double>> data;

    unsigned long size1{0};

    unsigned long size2{0};
};


#endif //CIRCUIT_SOLVER_MATRIX_H

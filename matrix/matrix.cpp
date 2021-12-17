//
// Created by Max on 12.12.2021.
//

#include "matrix.h"

#include <utility>

// create empty matrix(size1_, size2_)
matrix::matrix(unsigned long size1_, unsigned long size2_,
               string name_)
        : name{std::move(name_)}, size1{size1_}, size2{size2_} {
    data.resize(size1);
    for (auto &line: data) {
        line.resize(size2);
    }
}

matrix::matrix(vector<vector<double>> &data_, string name_)
        : name{std::move(name_)}, size1{data_.size()},
          size2{data_.at(0).size()} {
    data = data_;
}

matrix::matrix(vector<double> &data_, string name_)
        : name{std::move(name_)}, size1{data_.size()}, size2{1} {
    data = vector<vector<double>>(size1, vector<double>(size2));
    for (unsigned long i = 0; i < size1; i++) {
        data.at(i).at(0) = data_.at(i);
    }
}


matrix operator+(matrix &lhs, matrix &rhs) {
    if (lhs.size1 != rhs.size1 || lhs.size2 != rhs.size2) {
        throw length_error(string(__func__) +
                           ": matrix sizes are not the same");
    }
    matrix result(lhs.size1, lhs.size2);
    for (unsigned long i = 0; i < lhs.size1; i++) {
        for (unsigned long j = 0; j < lhs.size2; j++) {
            result.data.at(i).at(j) =
                    lhs.data.at(i).at(j) + rhs.data.at(i).at(j);
        }
    }
    return result;
}

matrix operator*(matrix &lhs, matrix &rhs) {
    auto result_matrix = lhs.multiply(rhs);
    return result_matrix;
}

matrix operator*(matrix &&lhs, matrix &rhs) {
    auto result_matrix = lhs.multiply(rhs);
    return result_matrix;
}

matrix operator*(matrix &&lhs, matrix &&rhs) {
    auto result_matrix = lhs.multiply(rhs);
    return result_matrix;
}

matrix operator*(matrix &lhs, matrix &&rhs) {
    auto result_matrix = lhs.multiply(rhs);
    return result_matrix;
}

matrix matrix::operator-() {
    matrix result_matrix(size1, size2);
    for (unsigned long i = 0; i < size1; i++) {
        for (unsigned long j = 0; j < size2; j++) {
            result_matrix.data.at(i).at(j) = -data.at(i).at(j);
        }
    }
    return result_matrix;
}


// print_data prints the matrix's data
void matrix::print_data() {
    cout << "Printing " << name << ":" << endl;
    for (auto &line: data) {
        for (auto &el: line) {
            cout << setw(10) << setprecision(3) << fixed;
            cout << el << " ";
        }
        cout << endl;
    }
}

// transpose return transposed matrix
matrix matrix::transpose() {
    auto tr_name = name + ".T";
    matrix transposed_matrix(size2, size1, tr_name);
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            transposed_matrix.data.at(j).at(i) = data.at(i).at(j);
        }
    }
    return transposed_matrix;
}

matrix matrix::multiply(matrix &m) {
    if (size2 != m.size1) {
        string error_m = __func__;
        error_m += ": incorrect matrix sizes; ";
        error_m +=
                "first matrix size = (k, " + to_string(size2) + "), ";
        error_m += "second matrix size = (" + to_string(m.size1) + ", n)\n";
        throw std::length_error(error_m);
    }
    vector<vector<double>> result_v(size1, vector<double>(m.size2));
    matrix result_matrix(result_v);

    for (int i = 0; i < result_matrix.size1; i++) {
        for (int j = 0; j < result_matrix.size2; j++) {
            // C_ij = A_ik * B_kj
            double i_j_result = 0;
            for (int k = 0; k < m.size1; k++)
                i_j_result += data.at(i).at(k) * m.data.at(k).at(j);
            result_matrix.data.at(i).at(j) = i_j_result;
        }
    }
    return result_matrix;
}


matrix matrix::inverse() {
    if (size1 != size2) {
        string error_m = __func__;
        error_m += ": matrix is not quadratic!";
        throw std::length_error(error_m);
    }
    auto size = size1;
    matrix tmp_matrix(data, "temporary matrix");
    matrix identity_matrix(size, size, "identity matrix");
    for (unsigned long i = 0; i < identity_matrix.size1; i++) {
        identity_matrix.data.at(i).at(i) = 1;
    }

    for (unsigned long i = 0; i < size; i++) {
        if (tmp_matrix.data[i][i] == 0) {
            // search for the column where [i][i] element != 0
            unsigned long k; // column swap index
            for (k = i + 1; k < size; k++) {
                // Go to right and find the column with non zero diag el
                if (tmp_matrix.data.at(i).at(k) != 0) {
                    break;
                }
            }
            if (k >= size) {
                string error_m = __func__;
                error_m += ": matrix is singular";
                throw std::invalid_argument(error_m);
            }
            tmp_matrix.swap_columns(i, k);
            identity_matrix.swap_columns(i, k);
        }
        // Make i-th diagonal element = 1
        double divider = tmp_matrix.data.at(i).at(i);
        for (unsigned long l = 0; l < size; l++) {
            tmp_matrix.data.at(i).at(l) /= divider;
            identity_matrix.data.at(i).at(l) /= divider;
        }
        // Straight run
        for (auto tmp = i + 1; tmp < size; tmp++) {
            auto coeff = -tmp_matrix.data.at(tmp).at(i);
            tmp_matrix.addition_of_lines(tmp, i, coeff);
            identity_matrix.addition_of_lines(tmp, i, coeff);
        }
    }
    // Reverse
    for (long i = long(size1 - 1); i >= 0; i--) {
        for (long tmp = i - 1; tmp >= 0; tmp--) {
            auto coeff = -tmp_matrix.data.at(tmp).at(i);
            tmp_matrix.addition_of_lines(tmp, i, coeff);
            identity_matrix.addition_of_lines(tmp, i, coeff);
        }
    }
    string new_name = name + "^(-1)";
    identity_matrix.rename(new_name);
    return identity_matrix;
}

void matrix::swap_columns(unsigned int column_n1, unsigned int column_n2) {
    if (column_n1 >= size2 || column_n2 >= size2) {
        string error_m = __func__;
        error_m += ": column number is greater then matrix size2";
        throw std::length_error(error_m);
    }
    for (unsigned long k = 0; k < size1; k++) {
        auto tmp = data.at(k).at(column_n1);
        data.at(k).at(column_n1) = data.at(k).at(column_n2);
        data.at(k).at(column_n2) = tmp;
    }
}

void matrix::addition_of_lines(unsigned int line_n1, unsigned int line_n2,
                               double coeff) {
    for (int j = 0; j < size2; j++) {
        data.at(line_n1).at(j) += data.at(line_n2).at(j) * coeff;
    }
}
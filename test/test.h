//
// Created by Max on 16.12.2021.
//

#ifndef CIRCUIT_SOLVER_TEST_H
#define CIRCUIT_SOLVER_TEST_H

#include "../includes/includes.h"
#include "../circuit/circuit.h"


bool compare_with_answer(matrix &current_vector, vector<double> &answer_vector);

void
print_test_info(bool &passed, int &test_number, vector<double> &answer_vector,
                matrix &current_vector);

class test {
public:
    test() = default;

    ~test() = default;

    void run_tests();

    static matrix get_results(string &input_data, int &test_counter);

    void first_test(int &test_number);

    void second_test(int &test_number);

    void third_test(int &test_number);

    void fourth_test(int &test_number);

    void fifth_test(int &test_number);

    void
    run_test(string &input_data, int &test_number,
             vector<double> &answer_vector);

private:
    int number_of_tests{0};
    int passed_tests{0};
};

#endif //CIRCUIT_SOLVER_TEST_H

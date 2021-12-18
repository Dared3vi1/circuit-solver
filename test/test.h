//
// Created by Max on 16.12.2021.
//

#ifndef CIRCUIT_SOLVER_TEST_H
#define CIRCUIT_SOLVER_TEST_H

#include "../includes/includes.h"
#include "../circuit/circuit.h"

template<typename T>
bool compare_with_answer(matrix<T> &current_vector,
                         vector<double> &answer_vector) {
    for (unsigned long i = 0; i < current_vector.get_size1(); i++) {
        if (current_vector.at(i).at(0) - answer_vector.at(i) >= 0.01)
            return false;
    }
    return true;
}

template<typename T>
void
print_test_info(bool &passed, int &test_number, vector<double> &answer_vector,
                matrix<T> &current_vector) {
    if (!passed) {
        cout << "Test #" << test_number << " failed\n";
        for (unsigned long i = 0; i < answer_vector.size(); i++) {
            cout << setprecision(5);
            cout << "[" << i << "] answer: " << current_vector.at(i).at(0)
                 << "  || ";
            cout << "Correct answer: " << answer_vector.at(i) << endl;
        }
        return;
    }
    cout << "Test #" << test_number << " passed\n";
}

class test {
public:
    test() = default;

    ~test() = default;

    void run_tests();
    
    matrix<double> get_results(string &input_data, int &test_counter);

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

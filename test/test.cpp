//
// Created by Max on 16.12.2021.
//

#include "test.h"

using namespace std;
namespace fs = std::filesystem;

void test::run_tests() {
    int i = 0;
    first_test(i);
    second_test(i);
    third_test(i);
    fourth_test(i);
    fifth_test(i);
    number_of_tests = i;
    cout << passed_tests << "/" << number_of_tests << " tests passed\n";
}

void test::first_test(int &test_number) {
    string input_data("3 -- 1, 161; 15V;"
                      "1 -- 2, 0; -24V;"
                      "2 -- 3, 0;"
                      "1 -- 4, 11000;"
                      "2 -- 4, 10;"
                      "3 -- 4, 18;");

    vector<double> answer_vector{-55.9 / 1000, -58.1 / 1000, -56.7 / 1000,
                                 2.2 / 1000, -1.4 / 1000, -0.78 / 1000};

    run_test(input_data, test_number, answer_vector);
}

void test::second_test(int &test_number) {
    string input_data("2 -- 1, 100; 5V;"
                      "1 -- 2, 10000;"
                      "1 -- 2, 510;");

    vector<double> answer_vector{8.54 / 1000, 0.415 / 1000, 8.13 / 1000};

    run_test(input_data, test_number, answer_vector);
}

void test::third_test(int &test_number) {
    string input_data("1 -- 2, 2; 1V;"
                      "1 -- 2, 4; -3V;"
                      "1 -- 2, 2; 5V;");

    vector<double> answer_vector{-0.4, -1.2, 1.6};

    run_test(input_data, test_number, answer_vector);
}

void test::fourth_test(int &test_number) {
    string input_data("2 -- 1, 0; 13V;"
                      "1 -- 3, 10;"
                      "1 -- 4, 10;"
                      "3 -- 4, 10;"
                      "3 -- 2, 10;"
                      "4 -- 2, 20;");

    vector<double> answer_vector{1.1, 0.6, 0.5, -0.1, 0.7, 0.4};

    run_test(input_data, test_number, answer_vector);
}

void test::fifth_test(int &test_number) {
    string input_data("1 -- 2, 10;"
                      "4 -- 1, 18; 20V;"
                      "3 -- 1, 5; 30V;"
                      "4 -- 3, 10;"
                      "2 -- 3, 8;"
                      "2 -- 4, 6;");

    vector<double> answer_vector{1.512, 0.09, 1.422, 0.451, 0.971, 0.542};

    run_test(input_data, test_number, answer_vector);
}

matrix<double> test::get_results(string &input_data, int &test_counter) {
    parser p(input_data);
    circuit c(&p);
    c.solve_circuit();
    test_counter++;
    return c.current_vector;
}


void test::run_test(string &input_data, int &test_number,
                    vector<double> &answer_vector) {
    matrix current_vector = get_results(input_data, test_number);

    bool passed = compare_with_answer(current_vector, answer_vector);
    if (passed) passed_tests++;

    print_test_info(passed, test_number, answer_vector, current_vector);
}
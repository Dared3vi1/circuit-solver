#include <iostream>
#include "./parser/parser.h"
#include "./matrix/matrix.h"
#include "./circuit/circuit.h"
#include "./test/test.h"

int main() {
    try {
        ifstream input_file("./input/input.txt");
        parser parser(input_file);
        circuit circuit(&parser);
        circuit.solve_circuit();
        ofstream output_file("./output/output.txt");
        circuit.output_answer(output_file);
        test test;
        test.run_tests();


    } catch (const std::exception &e) {
        cerr << "Error: " << e.what();
    }
}

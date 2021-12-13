#include <iostream>
#include "./parser/parser.h"
#include "./matrix/matrix.h"
#include "./circuit/circuit.h"

int main() {
    try {
        ifstream input_file("./input/input.txt");
        parser parser(input_file);
        circuit circuit(&parser);
        circuit.solve_circuit();
        ofstream output_file("./output/output.txt");
        circuit.output_answer(output_file);
    } catch (const std::exception &e) {
        cerr << "Error: " << e.what();
    }
}

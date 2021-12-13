#include <iostream>
#include "./parser/parser.h"
#include "./matrix/matrix.h"
#include "./circuit/circuit.h"

int main() {
    try {
//        matrix m(2, 2, "test");
//        m.print_data();
//        vector<vector<double>> test1{{1, 1},
//                                     {1, 2}};
//        vector<vector<double>> test2{{1, 0},
//                                     {0, 1}};
//        vector<vector<double>> test3{{1, 0},
//                                     {0, 1}};
//        matrix t1(test1, "test1");
//        matrix t2(test2, "test2");
//        matrix t3(test2, "test3");

//        cout << t2.size1 << " " << t2.size2;
//        t2.print_data();
//        auto t3 = t1 * t2;
//        t3.print_data();
//        auto t4 = -t1;
//        t4.rename("negative");
//        t4.print_data();
//        matrix t5 = t1.inverse();
//        t5.print_data();
//        matrix t6 = t3 * (t1 * t2);


        ifstream input_file("../input/input.txt");
        parser parser(input_file);
        circuit circuit(&parser);
        circuit.solve_circuit();


    } catch (const std::exception &e) {
        cerr << "Error: " << e.what();
    }
}

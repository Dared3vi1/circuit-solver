#include <iostream>
#include "./parser/parser.h"
#include "./matrix/matrix.h"

int main() {
    try {
        matrix m(2, 2, "test");
        m.print_data();
        vector<vector<double>> test1{{1, 1},
                                     {1, 2}};
        vector<vector<double>> test2{{1, 0},
                                     {0, 1},
                                     {1, 0}};
        matrix t1(test1);
        matrix t2(test2);
//        cout << t2.size1 << " " << t2.size2;
//        t2.print_data();
//        auto t3 = t1 * t2;
//        t3.print_data();
//        auto t4 = -t1;
//        t4.rename("negative");
//        t4.print_data();
        matrix t5 = t1.inverse();
        t5.print_data();

    } catch (const std::exception &e) {
        cerr << "Error: " << e.what();
    }
}

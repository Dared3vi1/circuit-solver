//
// Created by Max on 12.12.2021.
//

#ifndef CIRCUIT_SOLVER_PARSER_H
#define CIRCUIT_SOLVER_PARSER_H
#include "includes.h"

using namespace std;

struct entry_data {
    vector<unsigned int> vertices {0, 0};
    double resistance, voltage = 0;
};


class parser {
public:
    parser(ifstream& input_file) { parse(input_file); };
    ~parser() = default;

    void parse(ifstream &input_file);
    void print_entry_data() const;

    vector<entry_data>* get_entries() { return &entries; }

private:

    vector<entry_data> entries;

};

#endif //CIRCUIT_SOLVER_PARSER_H

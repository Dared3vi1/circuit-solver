//
// Created by Max on 12.12.2021.
//

#include "parser.h"


void parser::parse(ifstream &file) {
    string line;
    const char semicolon_symbol = ';';
    const char voltage_symbol = 'V';
    if (!file.is_open()) {
        perror("error while opening file");
    }
    while (getline(file, line)) {
        parse(line);
    }
    if (file.bad())
        perror("error while reading file");
}

void parser::parse(string &input_data) {
    const char semicolon_symbol = ';';
    const char voltage_symbol = 'V';
    string trash;
    auto begin_it = input_data.begin();
    auto end_it = input_data.end();
    string::iterator start_from_it;
    string::iterator s_it;
    for (; begin_it != end_it; begin_it = s_it + 1) {
        if (*begin_it == ' ') {
            s_it = begin_it;
            continue;
        }
        double resistance, voltage = 0;
        unsigned int first_vertex, second_vertex = 0;
        s_it = find(begin_it, end_it, semicolon_symbol);
        auto begin_index = distance(input_data.begin(), begin_it);
        auto end_index = begin_index + distance(begin_it, s_it);
        string entry = input_data.substr(begin_index, distance(begin_it, s_it));
        std::istringstream iss(entry);
        if (find(begin_it, s_it, voltage_symbol) != s_it) {
            iss >> voltage;
            entries.at(entries.size() - 1).voltage = voltage;
            start_from_it = s_it + 1;
            continue;
        }
        iss >> first_vertex >> trash >> second_vertex >> trash
            >> resistance;
        if (resistance == 0) {
            resistance = 0.0001;
        }
        entries.push_back(
                entry_data{{first_vertex, second_vertex}, resistance});
    }
//    cout << "Here \n";
}


void parser::print_entry_data() const {
    cout << "Printing entry data:" << endl;
    for (auto &entry: entries) {
        cout << entry.vertices.at(0) << " -- " << entry.vertices.at(1)
             << ", "
             << entry.resistance << ";";
        if (entry.voltage != 0) {
            cout << " " << entry.voltage << "V" << ";";
        }
        cout << endl;
    }
}
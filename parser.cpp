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
        // Vars, that will be needed for parsing
        string trash;
        auto begin_it = line.begin();
        auto end_it = line.end();
        string::iterator s_it;
        for (; begin_it != end_it; begin_it = s_it + 1) {
            double resistance, voltage = 0;
            unsigned int first_vertex, second_vertex = 0;
            s_it = find(begin_it, end_it, semicolon_symbol);
            auto begin_index = distance(line.begin(), begin_it);
            auto end_index = begin_index + distance(begin_it, s_it) + 1;
            string entry = line.substr(begin_index, end_index);
            std::istringstream iss(entry);
            if (auto v_it = find(begin_it, s_it, voltage_symbol) != s_it) {
                iss >> voltage;
                entries.at(entries.size() - 1).voltage = voltage;
                break;
            }
            iss >> first_vertex >> trash >> second_vertex >> trash
                >> resistance;
            if (resistance == 0) {
                resistance = 0.01;
            }
            entries.push_back(entry_data{{first_vertex, second_vertex},
                                         resistance});
        }
    }
    if (file.bad())
        perror("error while reading file");
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
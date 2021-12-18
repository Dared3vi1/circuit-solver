#include <iostream>
#include "./parser/parser.h"
#include "./matrix/matrix.h"
#include "./circuit/circuit.h"
#include "./test/test.h"

void help() {
    cout << "Help info:\n";
    cout << "-i <path_to_input_file>: specify path to input data file\n";
    cout << "-o <path_to_output_file>: specify path to output file\n";
    cout << "-t: run tests\n";
}

void
parse_command_line(map<string, string> &flags_args, int argc, char *argv[]) {
    if (argc == 1) {
        return;
    }
    string input, tmp_string;
    for (int i = 1; i < argc; i++) {
        input += string(argv[i]) + " ";
    }
    istringstream input_stream(input);
    while (input_stream >> tmp_string) {
        if (tmp_string == "-h") {
            help();
            flags_args["-h"] = "";
            return;
        }
        if (tmp_string == "-t") {
            flags_args["-t"] = "";
            return;
        }
        if (tmp_string == "-i") {
            input_stream >> tmp_string; // in_path_arg
            flags_args["-i"] = tmp_string;
        }
        if (tmp_string == "-o") {
            input_stream >> tmp_string; // out_path_arg
            flags_args["-o"] = tmp_string;
        }
    }
    if (flags_args.empty()) {
        cout << "Command line arguments are invalid\n";
        cout << "Use -h to see possible arguments\n";
    }
}


int main(int argc, char *argv[]) {
    map<string, string> flags_args;
    parse_command_line(flags_args, argc, argv);
    try {
        if (flags_args.contains("-h")) return 0;
        if (flags_args.contains("-t")) {
            test test;
            test.run_tests();
        } else {
            ifstream input_file;
            if (flags_args.contains("-i")) {
                input_file = ifstream(flags_args["-i"]);
            } else {
                input_file = ifstream("./input.txt");
            }
            parser parser(input_file);
            circuit circuit(&parser);
            circuit.solve_circuit();
            ofstream output_file;
            if (flags_args.contains("-o")) {
                output_file = ofstream(flags_args["-o"]);
            } else {
                output_file = ofstream("./output.txt");
            }
            circuit.output_answer(output_file);
        }

    } catch (const std::exception &e) {
        cerr << "Error: " << e.what();
    }
}

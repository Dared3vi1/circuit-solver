//
// Created by Max on 13.12.2021.
//

#ifndef CIRCUIT_SOLVER_CIRCUIT_H
#define CIRCUIT_SOLVER_CIRCUIT_H

#include "../parser/parser.h"
#include "../includes/includes.h"
#include "../matrix/matrix.h"

struct ioedges {
    set<unsigned int> input_edges;
    set<unsigned int> ouput_edges;
};

class circuit {
public:
    explicit circuit(parser *p_);

    ~circuit() = default;

    // Methods
    [[nodiscard]] string
    make_edge_key(const unsigned long &v1, const unsigned long &v2) const;

    void solve_circuit();

    void output_answer(ofstream &output_file);

    // Friends
    friend class test;

private:
    unsigned long number_of_vertices;
    unsigned long number_of_edges;
    parser *p;

    // Set for counting number of vertices
    set<unsigned long> vertices;

    // Directed initial adjacency list
    map<unsigned long, vector<unsigned long>> directed_adjacency_list;

    // Edge number to edge name mapping
    map<unsigned long, string> edges;

    // Edge to voltage mapping
    matrix<double> voltage_vector;

    // Edge to resistance mapping
    vector<double> resistance_vector;

    // Associate each vertex with input/output edges
    map<unsigned int, ioedges> vertex_ioedges;

    // Incidence Matrix (M)
    matrix<double> incidence_matrix;

    // Resistance matrix (R)
    matrix<double> resistance_matrix;

    // Conductivity matrix (G = 1/R)
    matrix<double> conductivity_matrix;

    // Result current vector
    matrix<double> current_vector;
};


#endif //CIRCUIT_SOLVER_CIRCUIT_H

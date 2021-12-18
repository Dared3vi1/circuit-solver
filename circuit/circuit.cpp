//
// Created by Max on 13.12.2021.
//

#include "circuit.h"

circuit::circuit(parser *p_) :
        p{p_} {
    auto entries = p->get_entries();
    unsigned int edge_counter = 0;
    vector<double> voltage_vector_data;
    for (auto &entry: *entries) {
        // Assign vertices
        auto tail_vertex = entry.vertices.at(0);
        auto head_vertex = entry.vertices.at(1);

        // Filling vertices set
        vertices.insert(tail_vertex);
        vertices.insert(head_vertex);

        // Filling directed_adjacency_list
        directed_adjacency_list[tail_vertex].push_back(head_vertex);

        // Filling eges
        string key = make_edge_key(tail_vertex, head_vertex);
        edges[edge_counter] = key;

        // Filling voltage_vector_data
        voltage_vector_data.push_back(entry.voltage);

        // Filling resistance vector
        resistance_vector.push_back(entry.resistance);

        // Filling vertex_ioedges
        vertex_ioedges[tail_vertex].ouput_edges.insert(edge_counter);
        vertex_ioedges[head_vertex].input_edges.insert(edge_counter);

        edge_counter++;
    }
    // Set number of vertices and edges
    number_of_vertices = vertices.size();
    number_of_edges = edge_counter;

    // Initialize voltage_vector
    voltage_vector = matrix<double>(number_of_edges, 1);
    for (unsigned long i = 0; i < number_of_edges; i++) {
        voltage_vector.at(i).at(0) = voltage_vector_data.at(i);
    }

    // Initializing incidence data and matrix
    vector<vector<double>> incidence_data;
    incidence_data.resize(number_of_vertices);
    for (auto &line: incidence_data) {
        line.resize(number_of_edges);
    }
    unsigned int i = 0;
    for (auto &el: vertex_ioedges) {
        for (auto &edge: el.second.ouput_edges) {
            incidence_data.at(i).at(edge) = 1;
        }
        for (auto &edge: el.second.input_edges) {
            incidence_data.at(i).at(edge) = -1;
        }
        i++;
    }
    // The (number of independent rows) equals (number of vertices - 1)
    incidence_data.pop_back();
    incidence_matrix = matrix(incidence_data, "incidence matrix");

    // Initializing resistance matrix and conductivity matrix
    vector<vector<double>> resistance_data;
    resistance_data.resize(number_of_edges);
    for (auto &line: resistance_data) {
        line.resize(number_of_edges);
    }

    vector<vector<double>> conductivity_data;
    conductivity_data.resize(number_of_edges);
    for (auto &line: conductivity_data) {
        line.resize(number_of_edges);
    }
    i = 0;
    for (auto &el: resistance_vector) {
        resistance_data.at(i).at(i) = el;
        conductivity_data.at(i).at(i) = 1 / el;
        i++;
    }
    resistance_matrix = matrix(resistance_data, "resistance matrix");
    conductivity_matrix = matrix(conductivity_data, "conductivity matrix");
}

void circuit::solve_circuit() {
    // To solve the circuit we will use the following formula:
    // Ф = (MGM^T)^(-1) * (-MGE) -- potential matrix
    // U = M^T*Ф                 -- voltages (without external) for each edge
    // I = G(U+E)                -- currents for each edge (answer)
    matrix<double> left_part = (incidence_matrix * conductivity_matrix *
                                incidence_matrix.transpose()).inverse();
    matrix<double> right_part =
            -incidence_matrix * conductivity_matrix * voltage_vector;
    matrix<double> potential_matrix = left_part * right_part;
    matrix<double> nat_voltage_vector =
            incidence_matrix.transpose() * potential_matrix;
    current_vector =
            conductivity_matrix * (nat_voltage_vector + voltage_vector);
    current_vector.rename("current_vector");
}

string circuit::make_edge_key(unsigned long v1, unsigned long v2) {
    string key;
    key = to_string(v1) + " -- " + to_string(v2);
    return key;
}

void circuit::output_answer(ofstream &output_file) {
    if (!output_file.is_open())
        perror("error while opening file");

    for (unsigned long i = 0; i < current_vector.get_size1(); i++) {
        string tmp =
                edges[i] + ": " + to_string(current_vector[i][0]) +
                " A;\n";
        output_file << tmp;
    }
    if (output_file.bad())
        perror("error while reading file");
}

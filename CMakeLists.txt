cmake_minimum_required(VERSION 3.21)
project(circuit_solver)

set(CMAKE_CXX_STANDARD 23)

add_executable(circuit_solver
        main.cpp
        parser/parser.cpp parser/parser.h
        includes/includes.h
        matrix/matrix.cpp matrix/matrix.h
        circuit/circuit.cpp circuit/circuit.h)

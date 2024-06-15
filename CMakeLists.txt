cmake_minimum_required(VERSION 3.10)

project(MyProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Define the source files for each target
set(SRC_IMP
        src/imp.cpp
        src/imp_parser.cpp
        src/imp_printer.cpp
        src/imp_typechecker.cpp
        src/imp_value.cpp
        src/imp_interpreter.cpp
        test/imp_test.cpp)

set(SRC_COMP
        src/imp.cpp
        src/imp_parser.cpp
        src/imp_printer.cpp
        src/imp_typechecker.cpp
        src/imp_value.cpp
        src/imp_interpreter.cpp
        src/imp_codegen.cpp
        test/imp_compiler.cpp)

set(SRC_SVM
        src/svm.cpp
        src/svm_parser.cpp
        test/svm_run.cpp)

# Create the executable for 'imp'
add_executable(imp ${SRC_IMP})

# Create the executable for 'compiler'
add_executable(compiler ${SRC_COMP})

# Create the executable for 'svm'
add_executable(svm ${SRC_SVM})
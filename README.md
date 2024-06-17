# Compiler for IMP-DEC Language

This project implements a compiler for the IMP-DEC language, written in C++. It includes a type checker and a code generator. The Doxygen documentation for the project can be found [here](https://rogerhuauya.com/compiler-imp-svml/).

## Grammar

The grammar for the IMP-DEC language is defined as follows:

```
Program      ::= Body
Body         ::= VarDecList StatementList
VarDecList   ::= (VarDec)*
VarDec       ::= "var" Type VarList ";"
Type         ::= id
VarList      ::= id ("," id)*
StatementList::= Stm (";" Stm)*
Stm          ::= id "=" Exp
| "print" "(" Exp ")"
| "if" Exp "then" Body ["else" Body] "endif"
| "while" Exp "do" Body "endwhile"
| "do" Body "while" Exp
Exp          ::= BExp
BExp         ::= CExp (("and" | "or") BExp)?
CExp         ::= AExp (("<" | "<=" | "==") AExp)?
AExp         ::= Term (("+" | "-") Term)*
Term         ::= Factor (("*" | "/") Factor)*
FExp         ::= Factor ("**" Factor)?
Factor       ::= num | "(" Exp ")" | id
```

Additionally, the language supports the `ifexp` construct:
```
"ifexp" "(" Exp "," Exp "," Exp ")"
```

## Features

### Type Checking and Code Generation

The project includes a type checker and a code generator for all expressions and statements defined by the grammar. The following features are implemented:

1. **Type Checker:** Ensures type safety in binary expressions, handling operations like addition, subtraction, multiplication, and division.
2. **Code Generator:** Generates SVML code corresponding to the IMP-DEC programs.

### Memory Allocation

The compiler assigns memory addresses to variables, starting from address 1. The memory addresses are efficiently reused within different scopes of the program.

### Comments

The IMP-DEC language supports single-line comments starting with `//` and ending at the end of the line.

### Do-While Loop

The compiler supports the `do-while` loop, allowing the execution of statements at least once before checking the condition.

## Example

```cpp
var int x, n;
n = 10;
x = 0;
if (x < n) {
    var bool a, b, x;
} else {
    var bool c, d;
}
endif;
```

## Compilation and Execution

To compile and run the compiler and the SVM, follow these instructions using CMake:

1. Create a build directory and navigate to it:
    ```sh
    mkdir build
    cd build
    ```

2. Generate the build files:
    ```sh
    cmake ..
    ```

3. Compile the projects:
    ```sh
    make
    ```

4. To compile and run an IMP-DEC program, use the `compiler` executable:
    ```sh
    ./compiler ../examples/example.imp
    ```

5. To run the SVM with the generated SVML code, use the `svm` executable:
    ```sh
    ./svm ../examples/example.imp ../examples/example.imp.sm
    ```

The above commands will parse, type check, interpret, and generate the SVML code for the input IMP-DEC program.

## Documentation

Detailed documentation for the project, including code references and explanations, can be found at the [Doxygen URL](https://rogerhuauya.com/compiler-imp-svml/).


## License

This project is licensed under the MIT License - see the LICENSE file for details.

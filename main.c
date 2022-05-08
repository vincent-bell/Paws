// define the implementations necessary for the header libraries
#define OP_IMPLEMENTATION 
#define SC_IMPLEMENTATION
#define FH_IMPLEMENTATION

// include the header libraries
#include <stdio.h>
#include <operations.h>
#include <interpreter.h>
#include <files.h>

#define MAX_PROG_SZ 10

// main program
int main (int argc, char **argv) {
    tuple *program;
    tuple p[MAX_PROG_SZ];

    if (argc != 2) {
        fprintf(stderr, "Usage: ./paws examples/myfile.iasm\n");
        exit(1);
    }

    program = conv_iasm_file(argv[1], p);
    for (int i = 0; i < 10; i++) {
        printf("program[%d] (size %zu) = (%d, %d)\n", i, program[i].size, program[i].values[0], program[i].values[1]);
    }
    interpret_program(program);
    return 0;
}

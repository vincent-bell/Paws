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
#define USAGE "Usage: ./paws examples/myfile.iasm\n"

void debug (tuple *program, char *mode) {
    if (strcmp(mode, "-d") == 0) {
        for (int i = 0; i < 10; i++) {
            printf("program[%d] (size %zu) = (%d, %d)\n", i, program[i].size, program[i].values[0], program[i].values[1]);
        }
    }
}

// main program
int main (int argc, char **argv) {
    static tuple *program;

    if (argc < 2) {
        fprintf(stderr, USAGE);
        fflush(stderr);
        exit(1);
    }

    program = conv_iasm_file(argv[1]);
    if (argc > 2) {
        debug(program, argv[2]);
    }
    interpret_program(program);
    test();
    return 0;
}

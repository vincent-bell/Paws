// define the implementations necessary for the header libraries
#define OP_IMPLEMENTATION 
#define SC_IMPLEMENTATION
#define LC_IMPLEMENTATION
#define FH_IMPLEMENTATION

// include the header libraries
#include <stdio.h>
#include <operations.h>
#include <interpreter.h>
#include <lcompiler.h>
#include <files.h>

#define USAGE "./paws action args -flags"

enum retcodes {SIM_W_NDEBUG, SIM_W_DEBUG, CMP_W_NDEBUG, NIM_ERROR};

void debug (tuple *program, char *mode) {
    if (strcmp(mode, "-d") == 0) {
        for (int i = 0; i < 32; i++) {
            printf("program[%d] (size %zu) = (%d, %d)\n", i, program[i].size, program[i].values[0], program[i].values[1]);
        }
    }
}

int evaluate_cmd_args (int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s ", USAGE);
        fflush(stderr);
        exit(1);
    }

    // need to implement some strong error return structure here without idea change
    switch (argc) {
        case 3:
            if (strcmp(argv[1], "simulate") == 0) {
                return SIM_W_NDEBUG;
            } else {
                return NIM_ERROR;
            }
            break;
        case 4:
            if (strcmp(argv[1], "simulate") == 0) {
                if (strcmp(argv[3], "-d") == 0) {
                    return SIM_W_DEBUG;
                } else {
                    return NIM_ERROR;
                }
            } else {
                return NIM_ERROR;
            }
        case 5:
            if (strcmp(argv[1], "compile") == 0) {
                return CMP_W_NDEBUG;
            } else {
                return NIM_ERROR;
            }
        default:
            return NIM_ERROR;
    }
    return NIM_ERROR;
}

// main program
int main (int argc, char **argv) {
    static tuple *program;

    int ret = evaluate_cmd_args(argc, argv);

    switch (ret) {
        case SIM_W_NDEBUG:
            program = conv_iasm_file(argv[2]);
            simulate_program(program);
            return 0;
        case SIM_W_DEBUG:
            program = conv_iasm_file(argv[2]);
            debug(program, argv[3]);
            simulate_program(program);
            return 0;
        case CMP_W_NDEBUG:
            program = conv_iasm_file(argv[2]);
            compile_program(program, argv[4]);
            return 0;
        case NIM_ERROR:
            fprintf(stderr, "[paws] An unknown error occured...\n");
            fflush(stderr);
            return 1;
    }
    return 0;
}

// include the header libraries
#include <stdio.h>
#include <operations.h>
#include <interpreter.h>
#include <wcompiler.h>
#include <lcompiler.h>
#include <files.h>

#define USAGE "./paws action args -flags"

enum retcodes {SIM_W_NDEBUG, SIM_W_DEBUG, LCMP_W_NDEBUG, WCMP_W_NDEBUG, NIM_ERROR};

typedef struct retObj {
    int retcode;
    char *msg;
} retObj;

char *getTupleContents (size_t size, signed int *ptr) {
    if (ptr == NULL) {
        return "NOP";
    } else {
        char *ret_string = (char *) malloc(sizeof(size)+1);
        if (size < 8) {
            sprintf(ret_string, "(%d, )", ptr[0]);
            return ret_string;
        } else {
            sprintf(ret_string, "(%d, %d)", ptr[0], ptr[1]);
            return ret_string;
        }
    }
}

void debug (tuple *program, char *mode) {
    if (strcmp(mode, "-d") == 0) {
        for (int i = 0; i < 32; i++) {
            printf("program[%d] (size %zu) = %s\n", i, program[i].size, getTupleContents(program[i].size, program[i].ptr));
        }
    }
}

retObj evaluateCmdArgs (int argc, char **argv) {
    retObj ret = {};
    if (argc < 3) {
        fprintf(stderr, "Usage: %s ", USAGE);
        fflush(stderr);
        exit(1);
    }

    switch (argc) {
        case 3:
            if (strcmp(argv[1], "simulate") == 0) {
                ret.retcode = SIM_W_NDEBUG;
                return ret;
            } else {
                ret.retcode = NIM_ERROR;
                sprintf(ret.msg, "Unknown subcommand %s", argv[1]);
                return ret;
            }
            break;
        case 4:
            if (strcmp(argv[1], "simulate") == 0) {
                if (strcmp(argv[3], "-d") == 0) {
                    ret.retcode = SIM_W_DEBUG;
                    return ret;
                } else {
                    ret.retcode = NIM_ERROR;
                    sprintf(ret.msg, "Unknown option %s", argv[3]);
                    return ret;
                }
            } else {
                ret.retcode = NIM_ERROR;
                sprintf(ret.msg, "Unknown subcommand %s", argv[1]);
                return ret;
            }
        case 5:
            if (strcmp(argv[1], "lcompile") == 0) {
                ret.retcode = LCMP_W_NDEBUG;
                return ret;
            } else if (strcmp(argv[1], "wcompile") == 0) {
                ret.retcode = WCMP_W_NDEBUG;
                return ret;
            } else {
                ret.retcode = NIM_ERROR;
                sprintf(ret.msg, "Unknown subcommand %s", argv[1]);
                return ret;
            }
        default:
            ret.retcode = NIM_ERROR;
            sprintf(ret.msg, "Unknown subcommand %s", argv[1]);
            return ret;
    }
    ret.retcode = NIM_ERROR;
    sprintf(ret.msg, "Unknown subcommand %s", argv[1]);
    return ret;
}

// main program
int main (int argc, char **argv) {
    static tuple *program;

    retObj ret = evaluateCmdArgs(argc, argv);
    switch (ret.retcode) {
        case SIM_W_NDEBUG:
            program = conv_iasm_file(argv[2]);
            simulate_program(program);
            return 0;
        case SIM_W_DEBUG:
            program = conv_iasm_file(argv[2]);
            debug(program, argv[3]);
            simulate_program(program);
            return 0;
        case LCMP_W_NDEBUG:
            program = conv_iasm_file(argv[2]);
            lcompile_program(program, argv[4]);
            return 0;
        case WCMP_W_NDEBUG:
            program = conv_iasm_file(argv[2]);
            wcompile_program(program, argv[4]);
            return 0;
        case NIM_ERROR:
            fprintf(stderr, "[paws] An unknown error occured...\n");
            fflush(stderr);
            return 1;
    }
    return 0;
}

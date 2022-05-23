// include the header libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <operations.h>
#include <interpreter.h>
#include <compiler.h>
#include <files.h>

#define USAGE "./paws action args -flags"

enum retcodes {SIM_W_NDEBUG, SIM_W_DEBUG, CMP_W_NDEBUG, NIM_ERROR};

typedef struct retObj {
    int retcode;
    char msg[91];
} retObj;

char *getTupleContents (size_t size, signed int *ptr) {
    if (ptr == NULL) {
        char *ret_string = (char *) malloc(sizeof(char) );
        tuple refTuple = ERROR(200); //define some error code for this in documentation soon "pointer to tuple values is null"
        sprintf(ret_string, "(%d, %d)", refTuple.ptr[0], refTuple.ptr[1]);
        return ret_string;
    } else {
        char *ret_string = (char *) malloc(sizeof(char) + 1);
        strcpy(ret_string, "(");
        size_t i = 0;
        while (i < size/4 - 1) {
            char strnum[11];
            sprintf(strnum, "%d", *(ptr + i));
            size_t numsz = strlen(strnum);
            char *tmp = (char *) malloc(sizeof(char) * numsz + 2);
            ret_string = (char *) realloc(ret_string, sizeof(char) * 13 * (i+1) + 2);
            sprintf(tmp, "%s, ", strnum);
            strncat(ret_string, tmp, 13);
            free(tmp);
            i++;
        }
        char strnum[11];
        sprintf(strnum, "%d", *(ptr + i));
        size_t fnumsz = strlen(strnum);
        ret_string = (char *) realloc(ret_string, sizeof(char) * 13 * (i+1) + fnumsz + 3);
        char tmp[fnumsz+1];
        switch (i) {
            case 0:
                sprintf(tmp, "%s, )", strnum);
                strncat(ret_string, tmp, 15);
                break;
            default:
                sprintf(tmp, "%s)", strnum);
                strncat(ret_string, tmp, 13);
                break;
        }
        return ret_string;
    }
}

void debug (tuple *program, char *mode) {
    if (strcmp(mode, "-d") == 0) {
        int i = 0;
        while (program[i].size != 0) {
            char *tuple = getTupleContents(program[i].size, program[i].ptr);
            printf("program[%d] (size %zu) = %s\n", i, program[i].size, tuple);
            free(tuple);
            i++;
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
            if (strcmp(argv[1], "compile") == 0) {
                ret.retcode = CMP_W_NDEBUG;
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

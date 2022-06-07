// Paws compiler v0.2.0 alpha

#include <stdio.h>
#include <assert.h>
#include <files.h>
#include <operations.h>

#define CCMP(OUTPATH) get_external_gpp(OUTPATH)

void compile_program (pawsTuple *program, char *outpath) {
    const char *target_filename = "Paws/program.c";
    FILE *fptr = fopen(target_filename, "w");
    if (fptr == NULL) {
        fprintf(stderr, "Failed to find the file %s\n", target_filename);
        fflush(stderr);
        exit(1);
    }

    fprintf(fptr, "#include <cstdio>\n");
    fprintf(fptr, "#include <operations.h>\n");
    fprintf(fptr, "#include <interpreter.h>\n\n");
    fprintf(fptr, "int main (void) {\n");
    fprintf(fptr, "    static tuple program[64];\n");

    size_t counter = 0;
    while (program[counter].ptr != NULL) {
        signed int operation = program[counter].ptr[0];
        assert(OP_COUNT == 6 && "The number of operations is currently out of sync");
        switch (operation) {

            case LINT32:
                fprintf(fptr, "    program[%zu] = LOAD_INT(%d);\n", counter, program[counter].ptr[1]);
                break;

            case I232_PLUS:
                fprintf(fptr, "    program[%zu] = ADDH();\n", counter);
                break;

            case I232_MINUS:
                fprintf(fptr, "    program[%zu] = SUBH();\n", counter);
                break;

            case I232_MULTIPLY:
                fprintf(fptr, "    program[%zu] = MULH();\n", counter);
                break;

            case I232_DUMP:
                fprintf(fptr, "    program[%zu] = DUMP();\n", counter);
                break;

        }
        free(program[counter].ptr);
        counter++;
    }

    fprintf(fptr, "    simulate_program(program);\n");
    fprintf(fptr, "    return 0;\n");
    fprintf(fptr, "}\n");

    printf("\033[31mTRYING TO EXEC: \"%s\"\033[0m\n", CCMP(outpath));
    if (!system(CCMP(outpath))) {
        printf("Invalid outpath: %s", outpath);
    }
}

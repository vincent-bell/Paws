// Paws compiler v0.2.0 alpha

#include <cstdio>
#include <cassert>
#include <operations.h>

void compile_program (tuple *program, char *target_filename) {
    FILE *fptr = fopen(target_filename, "w");
    if (fptr == NULL) {
        fprintf(stderr, "Failed to find the file %s\n", target_filename);
        fflush(stderr);
        exit(1);
    }

    fprintf(fptr, "// include the header libraries\n");
    fprintf(fptr, "#include <stdio.h>\n");
    fprintf(fptr, "#include <operations.h>\n");
    fprintf(fptr, "#include <interpreter.h>\n\n");
    fprintf(fptr, "int main (void) {\n");
    fprintf(fptr, "    static tuple program[64];\n");

    int i = 0;
    while (program[i].size > 0 && i < 64) {
        signed int operation = program[i].ptr[0];
        assert(OP_COUNT == 6 && "The number of operations is currently out of sync");
        switch (operation) {
            case LFAST32:
                fprintf(fptr, "    program[%d] = LOAD_FAST(%d);\n", i, program[i].ptr[1]);
                break;
            case I232_PLUS:
                fprintf(fptr, "    program[%d] = ADDH();\n", i);
                break;
            case I232_MINUS:
                fprintf(fptr, "    program[%d] = SUBH();\n", i);
                break;
            case I232_MULTIPLY:
                fprintf(fptr, "    program[%d] = MULH();\n", i);
                break;
            case I232_DUMP:
                fprintf(fptr, "    program[%d] = DUMP();\n", i);
                break;
        }
        free(program[i].ptr);
        i++;
    }

    fprintf(fptr, "    simulate_program(program);\n");
    fprintf(fptr, "}\n");
}

#ifndef WCOMPILER_H_
#define WCOMPILER_H_

#include <stdio.h>
#include <assert.h>

#ifndef WCDEF
#define WCDEF
#endif // WCDEF

WCDEF void wcompile_program (tuple *program, char *target_filename);

#endif // WCOMPILER_H_

#ifdef WC_IMPLEMENTATION

void wcompile_program (tuple *program, char *target_filename) {
    FILE *fptr = fopen(target_filename, "w");
    if (fptr == NULL) {
        fprintf(stderr, "Failed to find the file %s\n", target_filename);
        fflush(stderr);
        exit(1);
    }

    fprintf(fptr, "// define the implementations necessary for the header libraries\n");
    fprintf(fptr, "#define OP_IMPLEMENTATION\n");
    fprintf(fptr, "#define SC_IMPLEMENTATION\n\n");
    fprintf(fptr, "// include the header libraries\n");
    fprintf(fptr, "#include <stdio.h>\n");
    fprintf(fptr, "#include <operations.h>\n");
    fprintf(fptr, "#include <interpreter.h>\n\n");
    fprintf(fptr, "int main (void) {\n");
    fprintf(fptr, "    static tuple program[32];\n");

    int i = 0;
    while (program[i].size > 0 && i < 32) {
        signed int operation = program[i].values[0];
        i++;
        int lf = i - 1;
        assert(OP_COUNT == 6 && "The number of operations is currently out of sync");
        switch (operation) {
            case LFAST32:
                fprintf(fptr, "    program[%d] = LOAD_FAST(%d);\n", lf, program[lf].values[1]);
                break;
            case S232_PLUS:
                fprintf(fptr, "    program[%d] = S232_ADDH();\n", lf);
                break;
            case S232_MINUS:
                fprintf(fptr, "    program[%d] = S232_SUBH();\n", lf);
                break;
            case S232_MULTIPLY:
                fprintf(fptr, "    program[%d] = S232_MULH();\n", lf);
                break;
            case DUMP64:
                fprintf(fptr, "    program[%d] = OUTPUT64();\n", lf);
                break;
        }
    }

    fprintf(fptr, "    simulate_program(program);\n");
    fprintf(fptr, "}\n");
}

#endif // WC_IMPLEMENTATION

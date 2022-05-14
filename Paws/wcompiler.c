#include <stdio.h>
#include <process.h>
#include <assert.h>
#include <operations.h>

void conv_c2exe (char *c_filename, char *target_filename) {
    _execl(
        "C:\\Users\\vince\\scoop\\apps\\mingw\\current\\bin\\gcc.exe",
        "C:\\Users\\vince\\scoop\\apps\\mingw\\current\\bin\\gcc.exe",
        c_filename,
        "-o",
        target_filename,
        "-Iinclude",
        "-Wall",
        "-Wextra",
        NULL
    );
}

void wcompile_program (tuple *program, char *target_filename) {
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
                free(program[i].ptr);
                break;
            case S232_PLUS:
                fprintf(fptr, "    program[%d] = S232_ADDH();\n", i);
                free(program[i].ptr);
                break;
            case S232_MINUS:
                fprintf(fptr, "    program[%d] = S232_SUBH();\n", i);
                free(program[i].ptr);
                break;
            case S232_MULTIPLY:
                fprintf(fptr, "    program[%d] = S232_MULH();\n", i);
                free(program[i].ptr);
                break;
            case DUMP64:
                fprintf(fptr, "    program[%d] = OUTPUT64();\n", i);
                free(program[i].ptr);
                break;
        }
        i++;
    }

    fprintf(fptr, "    simulate_program(program);\n");
    fprintf(fptr, "}\n");
}

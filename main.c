#include <stdio.h>
#include <operations.h>
#include <interpreter.h>

int main (void) {
    tuple sampleProgram[] = {
        LOAD_FAST (150),
        LOAD_FAST (700),
        S232_ADDH(),
        OUTPUT64 (),
    };
    interpret_program(sampleProgram, 4);
    return 0;
}

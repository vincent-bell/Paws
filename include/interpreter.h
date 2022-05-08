#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <stdio.h>
#include <stdlib.h>

#ifndef INDEF
#define INDEF
#endif // INDEF

INDEF void interpret_program (tuple *program);

#endif // INTERPRETER_H_

#ifdef SC_IMPLEMENTATION

void interpret_program (tuple *program) {
    int stackPtr = 0;
    signed int stack[64]; // currently the simulator supports a maximum of 64 values on the stack at any given time
    size_t stack_sz = 0;

    int i = 0;
    while (program[i].size > 0 && i < 10) {
        signed int operation = program[i].values[0];
        if (operation == LFAST32) {
            if (stack_sz > 0) {
                stackPtr++;
                stack[stackPtr] = program[i].values[1];
            } else {
                stack[stackPtr] = program[i].values[1];
            }
            stack_sz = stack_sz + 4;
        } else if (operation == S232_PLUS) {
            stack[stackPtr-1] = stack[stackPtr] + stack[stackPtr-1];
            stackPtr--;
            stack_sz = stack_sz - 4;
        } else if (operation == S232_MINUS) {
            stack[stackPtr-1] = stack[stackPtr-1] - stack[stackPtr];
            stackPtr--;
            stack_sz =  stack_sz - 4;
        } else if (operation == S232_MULTIPLY) {
            stack[stackPtr-1] = stack[stackPtr] * stack[stackPtr-1];
            stackPtr--;
            stack_sz = stack_sz - 4;
        } else if (operation == DUMP64) {
            printf("%d\n", stack[stackPtr]);
            stack[stackPtr] = 0;
            stack_sz = stack_sz - 4;
            stackPtr--;
        } else if (operation == IVT_FAIL) {
            if (program[i].values[1] == 100) {
                printf("Invalid token error [100]\n");
            }
            exit(1);
        } else {
            printf("Failed to handle unknown opcode %d\n", program[i].values[0]);
        }
        i++;
    }
}

#endif

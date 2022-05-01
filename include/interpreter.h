#ifndef INTERPRETER_H_FILE
#define INTERPRETER_H_FILE

#include <stdio.h>
#include <operations.h>

void interpret_program (tuple *program, int total_ops) {
    int stackPtr = 0;
    signed int stack[64]; // currently the simulator supports a maximum of 64 values on the stack at any given time
    size_t stack_sz = 0;

    for (int i = 0; i < total_ops; i++) {
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
        } else {
            printf("Failed to handle unknown opcode %d\n", program[i].values[0]);
        }
    }
}

#endif

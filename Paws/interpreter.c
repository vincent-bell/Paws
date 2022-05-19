#include <stdlib.h>
#include <operations.h>

void debug_stack (signed int *stack, int pointer) {
    for (int i = 0; i < 10; i++) {
        printf("stack[%d] (stackPtr=%d) = %d\n", i, pointer, stack[i]);
    }
}

void simulate_program (tuple *program) {
    int stackPtr = 0;
    signed int *stack = calloc(64, sizeof(signed int)); // currently the simulator supports a maximum of 64 values on the virtual stack at any given time
    size_t stack_sz = 0;

    int i = 0;
    while (program[i].size > 0 && i < 32) {
        signed int operation = program[i].ptr[0];
        if (operation == LFAST32) {
            if (stack_sz > 0) {
                stackPtr++;
                stack[stackPtr] = program[i].ptr[1];
            } else {
                stack[stackPtr] = program[i].ptr[1];
            }
            stack_sz = stack_sz + 4;
            free(program[i].ptr);
        } else if (operation == I232_PLUS) {
            stack[stackPtr-1] = stack[stackPtr] + stack[stackPtr-1];
            stackPtr--;
            stack_sz = stack_sz - 4;
            free(program[i].ptr);
        } else if (operation == I232_MINUS) {
            stack[stackPtr-1] = stack[stackPtr-1] - stack[stackPtr];
            stackPtr--;
            stack_sz =  stack_sz - 4;
            free(program[i].ptr);
        } else if (operation == I232_MULTIPLY) {
            stack[stackPtr-1] = stack[stackPtr] * stack[stackPtr-1];
            stackPtr--;
            stack_sz = stack_sz - 4;
            free(program[i].ptr);
        } else if (operation == I232_DUMP) {
            printf("%d\n", stack[stackPtr]);
            stack[stackPtr] = 0;
            stack_sz = stack_sz - 4;
            stackPtr--;
        } else if (operation == I232_FAIL) {
            if (program[i].ptr[1] == 100) {
                printf("Invalid token error [100]\n");
                free(program[i].ptr);
            }
            exit(1);
        } else {
            printf("Failed to handle unknown opcode %d\n", program[i].ptr[0]);
            free(program[i].ptr);
            exit(1);
        }
        i++;
    }
    free(stack);
}

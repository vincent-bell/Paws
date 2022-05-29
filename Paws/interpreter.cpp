// Paws interpreter v0.2.0 alpha

#include <cstdlib>
#include <operations.h>

void debug_stack (signed int *stack, int pointer) {
    for (int i = 0; i < 3; i++) {
        printf("stack[%d] (stackPtr=%d) = %d\n", i, pointer, stack[i]);
    }
}

void simulate_program (tuple *program) {
    int stack[64] = {0};
    int stackPtr = 0;
    size_t stack_sz = 0;

    size_t counter = 0;
    while (program[counter].ptr != NULL) {
        int operation = program[counter].ptr[0];
        switch (operation) {

            case LINT32:
                if (stack_sz > 0) {
                    stackPtr++;
                    stack[stackPtr] = program[counter].ptr[1];
                } else {
                    stack[stackPtr] = program[counter].ptr[1];
                }
                stack_sz = stack_sz + 4;
                break;

            case I232_PLUS:
                stack[stackPtr-1] = stack[stackPtr] + stack[stackPtr-1];
                stackPtr--;
                stack_sz = stack_sz - 4;
                break;

            case I232_MINUS:
                stack[stackPtr-1] = stack[stackPtr-1] - stack[stackPtr];
                stackPtr--;
                stack_sz =  stack_sz - 4;
                break;

            case I232_MULTIPLY:
                stack[stackPtr-1] = stack[stackPtr] * stack[stackPtr-1];
                stackPtr--;
                stack_sz = stack_sz - 4;
                break;

            case I232_DUMP:
                printf("%d\n", stack[stackPtr]);
                stack[stackPtr] = 0;
                if (stackPtr > 0) {
                    stackPtr--;
                }
                stack_sz = stack_sz - 4;
                break;

            case I232_FAIL:
                if (program[counter].ptr[1] == 100) {
                    printf("Invalid token error [100]\n");
                }
                exit(1);
                break;

            default:
                printf("Failed to handle unknown opcode %d\n", program[counter].ptr[0]);
                exit(1);
                break;

        }
        free(program[counter].ptr);
        counter++;
    }
}

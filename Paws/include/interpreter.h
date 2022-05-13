#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <stdio.h>

void simulate_program (tuple *program);
void debug_stack (signed int *stack, int pointer);
signed int *init_stack (void);

#endif // INTERPRETER_H_

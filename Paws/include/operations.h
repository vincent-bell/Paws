#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <cstdio>

typedef struct pawsTuple {
    signed int *ptr;
    size_t size;
} pawsTuple;

enum operations {LINT32, I232_PLUS, I232_MINUS, I232_MULTIPLY, I232_DUMP, I232_FAIL, OP_COUNT};

char* getTupleContents(size_t size, int* ptr);
pawsTuple LOAD_INT (long long value);
pawsTuple ADDH (void);
pawsTuple SUBH (void);
pawsTuple MULH (void);
pawsTuple DUMP (void);
pawsTuple ERROR (int errid);

#endif // OPERATIONS_H_

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct tuple {
    signed int *ptr;
    size_t size;
} tuple;

enum operations {LFAST32, I232_PLUS, I232_MINUS, I232_MULTIPLY, I232_DUMP, I232_FAIL, OP_COUNT};

tuple LOAD_FAST (long long value);
tuple ADDH (void);
tuple SUBH (void);
tuple MULH (void);
tuple DUMP (void);
tuple ERROR (int errid);

#endif // OPERATIONS_H_

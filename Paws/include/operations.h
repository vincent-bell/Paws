#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct tuple {
    signed int *ptr;
    size_t size;
} tuple;

enum operations {LFAST32, S232_PLUS, S232_MINUS, S232_MULTIPLY, DUMP64, IVT_FAIL, OP_COUNT};

tuple LOAD_FAST (long long value);
tuple S232_ADDH (void);
tuple S232_SUBH (void);
tuple S232_MULH (void);
tuple OUTPUT64 (void);
tuple IVT_ERROR (int errid);

#endif // OPERATIONS_H_

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <limits.h>

#ifndef OPDEF
#define OPDEF
#endif // OPDEF

OPDEF typedef struct tuple {
    signed int values[5];
    size_t size;
} tuple;

OPDEF enum operations {LFAST32, S232_PLUS, S232_MINUS, S232_MULTIPLY, DUMP64, IVT_FAIL, OP_COUNT};

OPDEF tuple init_tuple (void);
OPDEF tuple LOAD_FAST (long long value);
OPDEF tuple S232_ADDH (void);
OPDEF tuple S232_SUBH (void);
OPDEF tuple s232_MULH (void);
OPDEF tuple OUTPUT64 (void);
OPDEF tuple IVT_ERROR (int errid);

#endif // OPERATIONS_H_

#ifdef OP_IMPLEMENTATION

OPDEF tuple init_tuple (void) {
    tuple refTuple;
    for (int i = 0; i < 5; i++) {
        refTuple.values[i] = 0;
    }
    refTuple.size = 0;
    return refTuple;
}

OPDEF tuple LOAD_FAST (long long value) {
    tuple refTuple = init_tuple();
    if (LONG_MIN < value && value < LONG_MAX) {
        refTuple.values[0] = LFAST32;
        refTuple.values[1] = value;
        refTuple.size = 8;
    } else {
        refTuple.values[0] = LFAST32;
        refTuple.values[1] = 0;
        refTuple.size = 8;
    }
    return refTuple;
}

OPDEF tuple S232_ADDH (void) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = S232_PLUS;
    refTuple.size = 4;
    return refTuple;
}

OPDEF tuple S232_SUBH (void) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = S232_MINUS;
    refTuple.size = 4;
    return refTuple;
}

OPDEF tuple S232_MULH (void) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = S232_MULTIPLY;
    refTuple.size = 4;
    return refTuple;
}

OPDEF tuple OUTPUT64 (void) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = DUMP64;
    refTuple.size = 4;
    return refTuple;
}

OPDEF tuple IVT_ERROR (int errid) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = IVT_FAIL;
    refTuple.values[1] = errid; // error code
    refTuple.size = 8;
    return refTuple;
}

#endif // OP_IMPLEMENTATION

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <operations.h>

tuple LOAD_INT (long long value) {
    tuple refTuple;
    refTuple.ptr = (int *) malloc(2 * sizeof(int));
    if (LONG_MIN <= value && value <= LONG_MAX) {
        refTuple.ptr[0] = LINT32;
        refTuple.ptr[1] = value;
        refTuple.size = 2 * sizeof(int);
    } else {
        refTuple.ptr[0] = LFAST32;
        refTuple.ptr[1] = 0;
        refTuple.size = 2 * sizeof(int);
    }
    return refTuple;
}

tuple ADDH (void) {
    tuple refTuple;
    refTuple.ptr = (int *) malloc(sizeof(int));
    refTuple.ptr[0] = I232_PLUS;
    refTuple.size = sizeof(int);
    return refTuple;
}

tuple SUBH (void) {
    tuple refTuple;
    refTuple.ptr = (int *) malloc(sizeof(int));
    refTuple.ptr[0] = I232_MINUS;
    refTuple.size = sizeof(int);
    return refTuple;
}

tuple MULH (void) {
    tuple refTuple;
    refTuple.ptr = (int *) malloc(sizeof(int));
    refTuple.ptr[0] = I232_MULTIPLY;
    refTuple.size = sizeof(int);
    return refTuple;
}

tuple DUMP (void) {
    tuple refTuple;
    refTuple.ptr = (int *) malloc(sizeof(int));
    refTuple.ptr[0] = I232_DUMP;
    refTuple.size = sizeof(int);
    return refTuple;
}

tuple ERROR (int errid) {
    tuple refTuple;
    refTuple.ptr = (int *) malloc(2 * sizeof(int));
    refTuple.ptr[0] = I232_FAIL;
    refTuple.ptr[1] = errid; // error code
    refTuple.size = 2 * sizeof(int);
    return refTuple;
}

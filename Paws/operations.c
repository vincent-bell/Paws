#include <stdio.h>
#include <operations.h>
#include <limits.h>

tuple LOAD_FAST (long long value) {
    tuple refTuple;
    refTuple.ptr = malloc(2 * sizeof(signed int));
    if (LONG_MIN <= value && value <= LONG_MAX) {
        refTuple.ptr[0] = LFAST32;
        refTuple.ptr[1] = value;
        refTuple.size = 2 * sizeof(signed int);
    } else {
        refTuple.ptr[0] = LFAST32;
        refTuple.ptr[1] = 0;
        refTuple.size = 2 * sizeof(signed int);
    }
    return refTuple;
}

tuple S232_ADDH (void) {
    tuple refTuple;
    refTuple.ptr = malloc(sizeof(signed int));
    refTuple.ptr[0] = S232_PLUS;
    refTuple.size = sizeof(signed int);
    return refTuple;
}

tuple S232_SUBH (void) {
    tuple refTuple;
    refTuple.ptr = malloc(sizeof(signed int));
    refTuple.ptr[0] = S232_MINUS;
    refTuple.size = sizeof(signed int);
    return refTuple;
}

tuple S232_MULH (void) {
    tuple refTuple;
    refTuple.ptr = malloc(sizeof(signed int));
    refTuple.ptr[0] = S232_MULTIPLY;
    refTuple.size = sizeof(signed int);
    return refTuple;
}

tuple OUTPUT64 (void) {
    tuple refTuple;
    refTuple.ptr = malloc(sizeof(signed int));
    refTuple.ptr[0] = DUMP64;
    refTuple.size = sizeof(signed int);
    return refTuple;
}

tuple IVT_ERROR (int errid) {
    tuple refTuple;
    refTuple.ptr = malloc(2 * sizeof(signed int));
    refTuple.ptr[0] = IVT_FAIL;
    refTuple.ptr[1] = errid; // error code
    refTuple.size = 2 * sizeof(signed int);
    return refTuple;
}

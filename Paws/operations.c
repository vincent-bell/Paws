#include <operations.h>
#include <limits.h>

tuple init_tuple (void) {
    tuple refTuple;
    for (int i = 0; i < 5; i++) {
        refTuple.values[i] = 0;
    }
    refTuple.size = 0;
    return refTuple;
}

tuple LOAD_FAST (long long value) {
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

tuple S232_ADDH (void) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = S232_PLUS;
    refTuple.size = 4;
    return refTuple;
}

tuple S232_SUBH (void) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = S232_MINUS;
    refTuple.size = 4;
    return refTuple;
}

tuple S232_MULH (void) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = S232_MULTIPLY;
    refTuple.size = 4;
    return refTuple;
}

tuple OUTPUT64 (void) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = DUMP64;
    refTuple.size = 4;
    return refTuple;
}

tuple IVT_ERROR (int errid) {
    tuple refTuple = init_tuple();
    refTuple.values[0] = IVT_FAIL;
    refTuple.values[1] = errid; // error code
    refTuple.size = 8;
    return refTuple;
}

#ifndef OPERATIONS_H_FILE
#define OPERATIONS_H_FILE

#define SIG32_MIN -2147483649
#define SIG32_MAX 2147483648
#define TUPLE_MAXVALUES 10

typedef struct tuple {
    signed int values[5];
    size_t size;
} tuple;

enum operations {LFAST32, S232_PLUS, S232_MINUS, S232_MULTIPLY, DUMP64};

tuple LOAD_FAST (long long value) {
    tuple refTuple;
    if (SIG32_MIN < value && value < SIG32_MAX) {
        refTuple.values[0] = LFAST32;
        refTuple.values[1] = value;
        refTuple.size = 4;
    } else {
        refTuple.values[0] = LFAST32;
        refTuple.values[1] = 0;
        refTuple.size = 4;
    }
    return refTuple;
}

tuple S232_ADDH (void) {
    tuple refTuple;
    refTuple.values[0] = S232_PLUS;
    refTuple.size = 4;
    return refTuple;
}

tuple S232_SUBH (void) {
    tuple refTuple;
    refTuple.values[0] = S232_MINUS;
    refTuple.size = 4;
    return refTuple;
}

tuple S232_MULH (void) {
    tuple refTuple;
    refTuple.values[0] = S232_MULTIPLY;
    refTuple.size = 4;
    return refTuple;
}

tuple OUTPUT64 (void) {
    tuple refTuple;
    refTuple.values[0] = DUMP64;
    refTuple.size = 4;
    return refTuple;
}

#endif

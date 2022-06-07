#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <operations.h>

char *getTupleContents (size_t size, int *ptr) {
    if (ptr == NULL) {
        char *ret_string = (char *) malloc(sizeof(char) );
        pawsTuple refTuple = ERROR(200); //define some error code for this in documentation soon "pointer to tuple values is null"
        sprintf(ret_string, "(%d, %d)", refTuple.ptr[0], refTuple.ptr[1]);
        return ret_string;
    } else {
        char *ret_string = (char *) malloc(sizeof(char) + 1);
        strcpy(ret_string, "(");
        size_t i = 0;
        while (i < size/4 - 1) {
            char strnum[11];
            sprintf(strnum, "%d", *(ptr + i));
            size_t numsz = strlen(strnum);
            char *tmp = (char *) malloc(sizeof(char) * numsz + 2);
            ret_string = (char *) realloc(ret_string, sizeof(char) * 13 * (i+1) + 2);
            sprintf(tmp, "%s, ", strnum);
            strncat(ret_string, tmp, 13);
            free(tmp);
            i++;
        }
        char strnum[11];
        sprintf(strnum, "%d", *(ptr + i));
        size_t fnumsz = strlen(strnum);
        ret_string = (char *) realloc(ret_string, sizeof(char) * 13 * (i+1) + fnumsz + 3);
        char tmp[fnumsz+1];
        if (i == 0) {
            sprintf(tmp, "%s, )", strnum);
            strncat(ret_string, tmp, 15);
        } else {
            sprintf(tmp, "%s)", strnum);
            strncat(ret_string, tmp, 13);
        }
        return ret_string;
    }
}

pawsTuple LOAD_INT (long long value) {
    pawsTuple refTuple;
    refTuple.ptr = (int *) malloc(2 * sizeof(int));
    if (LONG_MIN <= value && value <= LONG_MAX) {
        refTuple.ptr[0] = LINT32;
        refTuple.ptr[1] = value;
        refTuple.size = 2 * sizeof(int);
    } else {
        refTuple.ptr[0] = LINT32;
        refTuple.ptr[1] = 0;
        refTuple.size = 2 * sizeof(int);
    }
    return refTuple;
}

pawsTuple ADDH (void) {
    pawsTuple refTuple;
    refTuple.ptr = (int *) malloc(sizeof(int));
    refTuple.ptr[0] = I232_PLUS;
    refTuple.size = sizeof(int);
    return refTuple;
}

pawsTuple SUBH (void) {
    pawsTuple refTuple;
    refTuple.ptr = (int *) malloc(sizeof(int));
    refTuple.ptr[0] = I232_MINUS;
    refTuple.size = sizeof(int);
    return refTuple;
}

pawsTuple MULH (void) {
    pawsTuple refTuple;
    refTuple.ptr = (int *) malloc(sizeof(int));
    refTuple.ptr[0] = I232_MULTIPLY;
    refTuple.size = sizeof(int);
    return refTuple;
}

pawsTuple DUMP (void) {
    pawsTuple refTuple;
    refTuple.ptr = (int *) malloc(sizeof(int));
    refTuple.ptr[0] = I232_DUMP;
    refTuple.size = sizeof(int);
    return refTuple;
}

pawsTuple ERROR (int errid) {
    pawsTuple refTuple;
    refTuple.ptr = (int *) malloc(2 * sizeof(int));
    refTuple.ptr[0] = I232_FAIL;
    refTuple.ptr[1] = errid; // error code
    refTuple.size = 2 * sizeof(int);
    return refTuple;
}

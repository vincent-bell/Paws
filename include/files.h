#ifndef FILES_H_
#define FILES_H_

#define SV_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sv.h>

#ifndef FHDEF
#define FHDEF
#endif // FHDEF

FHDEF tuple parse_token_as_op (String_View token, size_t position, int line_no);
FHDEF tuple lex_line (char *line, int line_no);
FHDEF tuple *conv_iasm_file (char *fname);

#endif // FILES_H_

#ifdef FH_IMPLEMENTATION

#define MAX_PROG_SZ 32
#define MAX_LINE_SZ 20

FHDEF tuple parse_token_as_op (String_View token, size_t position, int line_no) {
    tuple sz_zero_tuple;
    sz_zero_tuple.size = 0;
    
    char token_str[MAX_LINE_SZ];
    sprintf(token_str, ""SV_Fmt"", SV_Arg(token));
    if (position > 0) {
        return LOAD_FAST(atoi(token_str));
    } else if (strcmp(token_str, "S232_ADDH") == 0) {
        return S232_ADDH();
    } else if (strcmp(token_str, "S232_SUBH") == 0) {
        return S232_SUBH();
    } else if (strcmp(token_str, "S232_MULH") == 0) {
        return S232_MULH();
    } else if (strcmp(token_str, "OUTPUT64") == 0) {
        return OUTPUT64();
    } else if (strcmp(token_str, "LOAD_FAST") == 0) {
        return sz_zero_tuple;
    } else {
        return IVT_ERROR(100);
    }
}

FHDEF tuple lex_line (char *line, int line_no) {
    tuple refTuple;
    char tfix[MAX_LINE_SZ];
    strncpy(tfix, line, MAX_LINE_SZ);

    String_View source = SV(tfix);
    const char *start = source.data;

    source = sv_trim_left(source);
    while (source.count > 0) {
        String_View token = sv_chop_by_delim(&source, ' ');
        size_t col = token.data - start;
        refTuple = parse_token_as_op(token, col, line_no);
        if (refTuple.size > 0) {
            return refTuple;
        }
        source = sv_trim_left(source);
    }
    return refTuple;
}

FHDEF tuple *conv_iasm_file (char *fname) {
    static tuple program[MAX_PROG_SZ];
    char buf[MAX_LINE_SZ];
    int line = 0;

    // initialize the program
    for (int i = 0; i < MAX_PROG_SZ; i++) {
        for (int j = 0; j < 5; j++) {
            program[i].values[j] = 0;
        }
        program[i].size = 0;
    }

    FILE *fptr = fopen(fname, "r");
    if (fptr == NULL) {
        fprintf(stderr, "Failed to find file %s\n", fname);
        fflush(stderr);
        exit(1);
    }
    while (fgets(buf, MAX_LINE_SZ, fptr)) {
        buf[strcspn(buf, "\n")] = 0;
        program[line] = lex_line(buf, line);
        line++;
    }
    fclose(fptr);

    return program;
}

#endif // FH_IMPLEMENTATION

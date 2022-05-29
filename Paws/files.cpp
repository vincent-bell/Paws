#include <cstdio>
#include <unistd.h>
#include <operations.h>
#define SV_IMPLEMENTATION
#include <sv.h>

#define MAX_LINE_SZ 23
#define MAX_PROG_SZ 64

tuple parse_token_as_op (String_View token, size_t position) {
    tuple sz_zero_t;
    sz_zero_t.size = 0;

    char token_str[MAX_LINE_SZ];
    sprintf(token_str, "" SV_Fmt "", SV_Arg(token));
    if (position > 0) {
        char *end = (char *) malloc(sizeof(char) * MAX_LINE_SZ);
        long long ifs = strtoll(token_str, &end, 10);
        return LOAD_INT(ifs);
    } else if (strcmp(token_str, "ADDH") == 0) {
        return ADDH();
    } else if (strcmp(token_str, "SUBH") == 0) {
        return SUBH();
    } else if (strcmp(token_str, "MULH") == 0) {
        return MULH();
    } else if (strcmp(token_str, "DUMP") == 0) {
        return DUMP();
    } else if (strcmp(token_str, "LOAD_INT") == 0) {
        return sz_zero_t;
    } else {
        return ERROR(100);
    }
}

tuple lex_line (char *line) {
    tuple refTuple;
    char tfix[MAX_LINE_SZ];
    strncpy(tfix, line, MAX_LINE_SZ);

    String_View source = SV(tfix);
    const char *start = source.data;

    source = sv_trim_left(source);
    while (source.count > 0) {
        String_View token = sv_chop_by_delim(&source, ' ');
        size_t col = token.data - start;
        refTuple = parse_token_as_op(token, col);
        if (refTuple.size > 0) {
            return refTuple;
        }
        source = sv_trim_left(source);
    }
    return refTuple;
}

tuple *conv_iasm_file (char *fname) {
    static tuple program[MAX_PROG_SZ]; 
    char buf[MAX_LINE_SZ];
    int line = 0;

    FILE *fptr = fopen(fname, "r");
    if (fptr == NULL) {
        fprintf(stderr, "Failed to find file %s\n", fname);
        fflush(stderr);
        exit(1);
    }
    while (fgets(buf, MAX_LINE_SZ, fptr)) {
        buf[strcspn(buf, "\n")] = 0;
        program[line] = lex_line(buf);
        line++;
    }
    fclose(fptr);

    return program;
}

char *get_external_gpp (char *outpath) {
    static char command[191] {};
    char s_outpath[MAX_LINE_SZ * 2];
    char buffer[MAX_LINE_SZ * 3];
    memcpy(s_outpath, outpath, MAX_LINE_SZ * sizeof(char));
    // Can we force the outpath to be absolute or will it always be relative?
    sprintf(command, "g++ Paws/program.cpp Paws/operations.cpp Paws/interpreter.cpp -o %s -IPaws/include", s_outpath);
    printf("COMMAND: %s, CURRENT DIR: %s\n", command, getcwd(buffer, sizeof(buffer)));
    return command;
}

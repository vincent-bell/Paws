#ifndef FILES_H_
#define FILES_H_

#include <operations.h>
#include <sv.h>

tuple parse_token_as_op (String_View token, size_t position);
tuple lex_line (char *line);
tuple *conv_iasm_file (char *fname);
char *get_external_gpp (char *outpath);

#endif // FILES_H_

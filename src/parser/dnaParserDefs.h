#ifndef _H_DNA_PARSER_DEFS_
#define _H_DNA_PARSER_DEFS_

#include "DNALoader.h"
#include "DNAStorage.h"

void dna_init_parser(std::istream &in, const std::string &filename,
                     DNALoader* loader, DNAStorage* store,
                     PT(DNAGroup) root);
void dna_cleanup_parser();
int dnayyparse();

// This structure holds the return value for each token.  Traditionally, this
// is a union, and is declared with the %union declaration in the parser.y
// file, but unions are pretty worthless in C++ (you can't include an object
// that has member functions in a union), so we'll use a class instead.  That
// means we need to declare it externally, here.

class DNATokenType {
public:
  union U {
    uint64_t uint64;
    int64_t int64;
    double real;
  } u;
  std::string str;
  std::vector<std::string> str_vec;
  LPoint3f point3;
};

// The yacc-generated code expects to use the symbol 'YYSTYPE' to refer to the
// above class.
#define YYSTYPE DNATokenType

#endif

#ifndef _H_DNA_LEXER_DEFS_
#define _H_DNA_LEXER_DEFS_

#include "dnabase.h"

void dna_init_lexer(std::istream &in, const std::string &filename);
int dna_error_count();
int dna_warning_count();

void dnayyerror(const std::string &msg);
void dnayywarning(const std::string &msg);

int dnayylex();

// we always read files
#define YY_NEVER_INTERACTIVE 1
#endif

#include "parser.hh"

enum Type{Int, Char};

enum Type typeInfer(struct Tree * tree);
void analyzeSemantics(struct Env * prog);
#include "parser.hh"
#include <bits

class Type {
    std::string type;
    public:
        Type(std::string type) {
            this.type = type;
        }
}

Type IntType = new Type("Int");
Type CharType = new Type("Char");

enum Type typeInfer(struct Tree * tree);
void analyzeSemantics(struct Env * prog);
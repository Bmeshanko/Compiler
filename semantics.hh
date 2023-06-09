#include "parser.hh"
#include <bits
using namespace std;

class Type {
    std::string type;
    public:
        Type(std::string type) {
            this.type = type;
        }

        toString() {
            return type;
        }
}

Type IntType = new Type("Int");
Type CharType = new Type("Char");

class FunType : Type {
    vector<pair<std::string, Type>> args;

    public:
        Type(vector<pair<std::string, Type>> args) {
            this.args = args;
        }

        toString() {
            std::string ret = "(";
            for (arg : args) {
                ret += "[" + arg.first() + ", " + arg.second + "]";
            }
            ret += ")";
            return ret;
        }
}

enum Type typeInfer(struct Tree * tree);
void analyzeSemantics(struct Env * prog);
#include "parser.hh"
#include <bits
using namespace std;

#define N 1000

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
Type UnitType = new Type("Unit"); // i.e. a Variable Declaration/If Statement is UnitType.

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

struct TypedTree {
    Type element_type;
    int tree_type;
}

struct TypedEnv {
    struct TypedTree * prog[N];
    int lines;
}



enum Type typeInfer(struct Tree * tree);
void analyzeSemantics(struct Env * prog);
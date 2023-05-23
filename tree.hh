#include <vector>
#include <string>
#include <map>
#include <cstdlib>

class Tree {
    public:
        char* to_string() {
            return (char*) "Tree";
        }
};

class AST {
    std::vector<Tree> nodes;
    public:
        AST() {
            
        }
};

class Prim : public Tree {
    char op;
    Tree arg1;
    Tree arg2;
    public:
        Prim(char op, Tree arg1, Tree arg2) {
            this -> op = op;
            this -> arg1 = arg1;
            this -> arg2 = arg2;
        }
        
        char* to_string() {
            return (char*) "Prim(%c, %s, %s)", op, arg1.to_string(), arg2.to_string();
        }
};

class Lit : public Tree {
    int value;
    public:
        Lit(int value) {
            this -> value = value;
        }

        char* to_string() {
            char* buf;
            sprintf(buf, "Lit(%d)", value);
            return buf;
        }
};

class Let : Tree {
    std::string name;
    Tree value;
};

class Ref : Tree {
    std::string name;
};

class Env {
    std::map<std::string, int> vars;

    bool isDefined(std::string name) {
        return vars.count(name) > 0;
    }

    int getVar(std::string name) {
        return vars[name];
    }
    
    void varDec(std::string name, int value) {
        if (isDefined(name)) {
            fprintf(stderr, "Error: Variable %s is already defined.\n", name.c_str());
        } else {
            vars[name] = value;
        }
    }

    void varAssign(std::string name, int value) {
        if (!isDefined(name)) {
            fprintf(stderr, "Error: Variable %s is undefined.\n", name.c_str());
        } else {
            vars[name] = value;
        }
    }
};

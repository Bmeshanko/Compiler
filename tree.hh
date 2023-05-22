#include <vector>
#include <string>
#include <map>

class Tree {
    
};

class Prim : Tree {
    char op;
    std::vector<Tree> args;
};

class Lit : Tree {
    int value;
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
        return vars.contains(name);
    }

    int getVar(std::string name) {
        return vars[name];
    }
    
    void varDec(std::string name, int value) {
        if (isDefined(name)) {
            fprintf(stderr, "Variable " + name.c_str() + " is already defined!\n");
        } else {
            vars[name] = value;
        }
    }

    void varAssign(std::string name, int value) {
        if (!isDefined(name)) {
            fprintf(stderr, "Variable " + name.c_str() + " is not yet defined!\n");
        } else {
            vars[name] = value;
        }
    }
}

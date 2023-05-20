#include <vector>
#include <string>

class Tree {

};

class Prim : Tree {
    char op;
    std::vector<Tree> args;
};

class Lit : Tree {
    int value;
}

class Let : Tree {
    std::string name;
    Tree value;
}

class Ref : Tree {

}

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>

typedef std::map<std::string, int> mci;

void eval(struct Env *prog, int start, int end, mci &variables);
int findEnd(struct Env *prog, int start);
int evalFun(struct Env *prog, int start, mci &variables);
void evalLet(struct Env *prog, struct Let *let, mci &variables);
bool evalCond(struct Env *prog, struct Tree *tree, int type, mci &variables);
int evalNum(struct Env *prog, struct Tree *tree, mci &variables);
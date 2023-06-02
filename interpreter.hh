#include <stdlib.h>
#include <stdio.h>

void eval (struct Env *prog);
void evalGeneric(struct Tree *tree);
void evalFromTo(struct Env *prog, int start, int end);
void evalLet(struct Let *let);
bool evalIf(struct If *ifs);
bool evalWhile(struct While *whiles);
int evalNum(struct Tree *tree);
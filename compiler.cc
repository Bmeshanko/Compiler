#include <cstdlib>
#include <cstdio>
#include <vector>
#include "compiler.hh"



Compiler::Compiler() {
	nums = std::vector<int>();
	ops = std::vector<char>();
}

void Compiler::insertNum(int num) {
	nums.push_back(num);
}

void Compiler::insertOp(char op) {
	ops.push_back(op);
}

#include <cstdlib>
#include <cstdio>
#include <vector>
#include "compiler.hh"

Compiler::Compiler() {
	nums = std::vector<int>();
}

void Compiler::insertNum(int num) {
	nums.push_back(num);
}

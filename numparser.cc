#include <vector>
#include "numparser.hh"
#include "compiler.hh"

Numparser::Numparser() {
	nums = std::vector<int>();
	ops = std::vector<char>();
}

void insertNum(int num) {
	nums.push_back(num);
}

void insertOp(char op) {
	ops.push_back(op);
}

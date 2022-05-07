#include <vector>
#include "numparser.hh"

Numparser::Numparser() {
	_nums = std::vector<int>();
	_ops = std::vector<char>();
}

void insertNum(int num) {
	_nums.push_back(num);
}

void insertOp(char op) {
	_ops.push_back(op);
}

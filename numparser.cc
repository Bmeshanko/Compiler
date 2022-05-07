#include <vector>
#include "numparser.hh"

Numparser::Numparser() {
	_nums = std::vector<int>();
	_ops = std::vector<char>();
}

void insertNum(int num) {
	Numparser::_nums.push_back(num);
}

void insertOp(char op) {
	Numparser::_ops.push_back(op);
}

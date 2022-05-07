#include <vector>
#include "numparser.hh"

Numparser::Numparser() {
	nums = std::vector<int>();
	ops = std::vector<char>();
}

void Numparser::insertNum( int num ) {
	nums.push_back(num);
}

void Numparser::insertOp(char op) {
	ops.push_back(op);
}

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

void Numparser::print() {
	for (int i = 0; i < nums.size(); i++) {
		printf("%d", nums.at(i));
	}

	for (int i = 0; i < ops.size(); i++) {
		printf("%c", nums.at(i));
	}
}

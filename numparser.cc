#include <vector>
#include <stdio.h>
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

	if (nums.size() - 1 != ops.size()) {
		perror("Invalid Equation!");
		exit(-1);
	}
	
	for (int i = 0; i < nums.size(); i++) {
		printf("%d", nums.at(i));
	}

	for (int i = 0; i < ops.size(); i++) {
		printf("%c", ops.at(i));
	}
}

void Numparser::evaluate() {
	if (nums.size() - 1 != ops.size()) {
		perror("Invalid Equation!");
		exit(-1);
	}
}

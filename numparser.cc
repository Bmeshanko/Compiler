#include <vector>
#include <stdio.h>
#include <stdlib.h>
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
	if (nums.size() - 1 != ops.size() || nums.size() != 2) {
		perror("Invalid Equation!");
		exit(-1);
	}
	
	int num;
	switch (ops.at(0)) {
		case '+':
			num = nums.at(0) + nums.at(1);
			break;
		case '-':
			num = nums.at(0) - nums.at(1);
			break;
		case '*':
			num = nums.at(0) * nums.at(1);
			break;
		case '/':
			num = num.at(0) / nums.at(1);
			break;
		case '%':
			num = num.at(0) % nums.at(1);
			break;
	}
	nums.clear();
	ops.clear();
	nums.push_back(num);
}


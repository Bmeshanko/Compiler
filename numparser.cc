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
		//perror("Invalid Equation!");
		//exit(-1);
	}
	
	for (int i = 0; i < nums.size(); i++) {
		printf("%d", nums.at(i));
	}

	for (int i = 0; i < ops.size(); i++) {
		printf("%c", ops.at(i));
	}
	printf("\n");
}

void Numparser::evaluate() {
	if (nums.size() - 1 != ops.size() || nums.size() != 2) {
		//perror("Invalid Equation!");
		//exit(-1);
	}
	
	int num1 = nums.pop_back();
	int num2 = nums.pop_back();
	char op = ops.pop_back();

	int res;

	switch (op) {
		case '+':
			res = num1 + num2
			break;
		case '-':
			res = num1 - num2;
			break;
		case '*':
			res = num1 * num2;
			break;
		case '/':
			res = num1 / num2;
			break;
		case '%':
			res = num1 % num2;
			break;
	}

	fprintf(stderr, "\n\nHey\n\n");
	nums.push_back(num);
	print();
}


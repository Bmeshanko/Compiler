#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "numparser.hh"

Numparser::Numparser() {
	nums = std::vector<int>();
	ops = std::vector<char>();
}

void Numparser::insertNum(int num) {
	nums.push_back(num);
}

void Numparser::insertOp(char op) {
	ops.push_back(op);
}

void Numparser::print() {
	// TODO: Error Checking.
	
	for (int i = 0; i < nums.size(); i++) {
		printf("%d", nums.at(i));
	}

	for (int i = 0; i < ops.size(); i++) {
		printf("%c", ops.at(i));
	}
	printf("\n");
}

void Numparser::evaluateAll() {
	// Evaluates all numerical equations

	if (nums.size() - 1 != ops.size()) {
		perror("Invalid Equation.");
		exit(-1);
	}

	evaluateOp('^');
	evaluateOp('%');
	evaluateOpLR('*', '/');
	evaluateOpLR('+', '-');
	
	print();

}

void Numparser::evaluateOp(char op) {
	for (int i = ops.size() - 1; i >= 1; i--) {
		if (ops.at(i - 1) == op) {
			int res = evaluateSimple(nums.at(i), nums.at(i - 1), op);

			nums.erase(nums.begin() + i);
			nums.erase(nums.begin() + i);

			nums.insert(nums.begin() + i, res);

			ops.erase(ops.begin() + i);
		}
	}
}

void Numparser::evaluateOpLR(char op1, char op2) {
	for (int i = ops.size() - 1; i >= 1; i--) {
		if (ops.at(i - 1) == op1) {
			int res = evaluateSimple(nums.at(i), nums.at(i - 1), op1);

			nums.erase(nums.begin() + i);
			nums.erase(nums.begin() + i);

			nums.insert(nums.begin() + i, res);

			ops.erase(ops.begin() + i);
		} else if (ops.at(i - 1) == op2) {
			int res = evaluateSimple(nums.at(i), nums.at(i - 1), op2);

			nums.erase(nums.begin() + i);
			nums.erase(nums.begin() + i);

			nums.insert(nums.begin() + i, res);

			ops.erase(ops.begin() + i);
		}
	}
}

int Numparser::evaluateSimple(int num2, int num1, char op) {
	// Evaluates a numerical equation with two operators.
	// Numbers are given in reverse order, so we must switch the order.

	int res;

	switch (op) {
		case '+':
			res = num1 + num2;
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

	fprintf(stderr, "\n\n%c %d %d %d\n\n", op, res, num1, num2);

	return res;

}


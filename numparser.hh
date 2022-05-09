#ifndef numparser_hh
#define shell_hh

#include <vector>

struct Numparser {
	std::vector<int> nums;

	std::vector<char> ops;

	void insertNum(int num);

	void insertOp(char op);

	void print();
	
	void evaluateAll();

	void evaluateOp(char op);

	void evaluateOpLR(char op1, char op2);
	
	int evaluateSimple(int num1, int num2, char op);

	Numparser();
};

#endif

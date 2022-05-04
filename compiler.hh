#include <vector>

struct Compiler {
	std::vector<int> nums;
	std::vector<char> ops;
	Compiler();
	void insertNum(int num);
	void insertOp(char op);
};

#include <vector>

struct Numparser {
	std::vector<int> nums;
	std::vector<char> ops;
	void insertNum(int num);
	void insertOp(char op);
	Numparser();
};

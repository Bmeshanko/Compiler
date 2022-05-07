#ifndef numparser_hh
#define shell_hh

#include <vector>

struct Numparser {
	static std::vector<int> nums;
	static std::vector<char> ops;
	static void insertNum(int num);
	static void insertOp(char op);
	Numparser();
};

#endif

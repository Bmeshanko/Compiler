#ifndef numparser_hh
#define shell_hh

#include <vector>

struct Numparser {
	static std::vector<int> _nums;
	static std::vector<char> _ops;
	void insertNum(int num);
	void insertOp(char op);
	Numparser();
};

#endif

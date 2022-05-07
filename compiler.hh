#ifndef command_hh
#define command_hh

#include <vector>
#include "numparser.hh"

struct Compiler {
	Compiler();
	static Numparser _currentNumparser;
};

#endif

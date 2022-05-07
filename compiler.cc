#include <cstdlib>
#include <cstdio>
#include <vector>
#include "compiler.hh"

Compiler::Compiler() {
	_currentNumparser = new Numparser();	
}

Numparser * Compiler::_currentNumparser;

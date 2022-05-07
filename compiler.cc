#include <cstdlib>
#include <cstdio>
#include <vector>
#include "compiler.hh"

Compiler::Compiler() {
	_numparser = new Numparser();	
}

Numparser * Compiler::_numparser;

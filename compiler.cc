#include <cstdlib>
#include <cstdio>
#include <vector>
#include "compiler.hh"

Numparser Compiler::_np;

Compiler::Compiler() {
	_np = new Numparser();
}

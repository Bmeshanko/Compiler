#include <cstdlib>
#include <cstdio>
#include <vector>
#include "compiler.hh"

Numparser *_np;

Compiler::Compiler() {
	_np = new Numparser();
}

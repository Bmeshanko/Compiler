#include <cstdlib>
#include <cstdio>
#include <vector>
#include "compiler.hh"

static Numparser *_np;

Compiler::Compiler() {
	_np = new Numparser();
}

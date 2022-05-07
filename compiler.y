%code requires
{
	#include <string>
}

%union
{
	std::string* num_string;
}

%token <num_string> NUMBER
%token ADD SUBTRACT MULTIPLY DIVIDE MODULE

%{

#include "compiler.hh"
#include <stdlib.h>

void yyerror(const char * s);
int yylex();


%}

%%
 
goal:
	command
	;

command:
	number
	;

number:
	NUMBER {
		std::string * nstr = new std::string ( *$1 );
		int num = atoi(nstr->c_str());
		Compiler::_np.insertNum(num);
	}
	|
	NUMBER operator number {
		std::string * nstr = new std::string ( *$1 );
		int num = atoi(nstr->c_str());
		Compiler::_np.insertNum(num);
		Compiler::_np.evaluate();
	}
	;

operator:
	ADD {
		char op = '+';
		Compiler::_np.insertOp(op);
	}
	| SUBTRACT {
		char op = '-';
		Compiler::_np.insertOp(op);
	}
	| MULTIPLY {
		char op = '*';
		Compiler::_np.insertOp(op);
	}
	| DIVIDE {
		char op = '/';
		Compiler::_np.insertOp(op);
	}
	| MODULE {
		char op = '%';
		Compiler::_np.insertOp(op);
	}
	;

%%

void yyerror(const char * s) {
	fprintf(stderr, "%s", s);
}


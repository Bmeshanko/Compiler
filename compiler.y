%code requires
{
	#include <string>
}

%union
{
	std::string* num_string;
	char num_operator;
}
%token <num_string> NUMBER
%token <num_operator> ADD SUBTRACT MULTIPLY DIVIDE MODULE

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
		fprintf(stderr, "%d", num);
		Compiler::_np.insertNum(num);
	}
	|
	NUMBER operator number {
		std::string * nstr = new std::string ( *$1 );
		int num = atoi(nstr->c_str());
		fprintf(stderr, "%d", num);
		Compiler::_np.insertNum(num);
	}
	;

operator:
	ADD {
		char op = $1;
		Compiler::_np.insertOp(op);
		Compiler::_np.print();
	}
	| SUBTRACT {
		char op = $1;
		Compiler::_np.insertOp(op);
	}
	| MULTIPLY {
		char op = $1;
		Compiler::_np.insertOp(op);
	}
	| DIVIDE {
		char op = $1;
		Compiler::_np.insertOp(op);
	}
	| MODULE {
		char op = $1;
		Compiler::_np.insertOp(op);
	}
	;

%%

void yyerror(const char * s) {
	fprintf(stderr, "%s", s);
}


%code requires
{
	#include <string>
}

%union
{
	std::string* num_string;
	std::string* func_string;
	std::string* args_string;
}

%token <num_string> NUMBER
%token <func_string> <args_string> FUNCTION
%token ADD SUBTRACT MULTIPLY DIVIDE MODULE EXPONENT SEMICOLON 

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
	function arguments end
	;

function:
	FUNCTION {
		std::string * func_str = new std::string ( *$1 );
		printf("%s", func_str->c_str());
	}
	;

arguments:
	number
	;

end:
	SEMICOLON {
		Compiler::_np.evaluateAll();
	}
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
	}
	;

operator:
	ADD {
		Compiler::_np.insertOp('+');
	}
	| SUBTRACT {
		Compiler::_np.insertOp('-');
	}
	| MULTIPLY {
		Compiler::_np.insertOp('*');
	}
	| DIVIDE {
		Compiler::_np.insertOp('/');
	}
	| MODULE {
		Compiler::_np.insertOp('%');
	}
	| EXPONENT {
		Compiler::_np.insertOp('^');
	}
	;

%%

void yyerror(const char * s) {
	fprintf(stderr, "%s", s);
}


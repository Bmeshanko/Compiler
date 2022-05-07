%code requires
{
	#include <string>
}

%union
{
	std::string* num_string;
	char operator;
}
%token <num_string> NUMBER
%token <operator> ADD SUBTRACT MULTIPLY DIVIDE MODULE

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
	NUMBER
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

	}
	| SUBTRACT {

	}
	| MULTIPLY {

	}
	| DIVIDE {

	}
	| MODULE {
		
	}
	;

%%

void yyerror(const char * s) {
	fprintf(stderr, "%s", s);
}


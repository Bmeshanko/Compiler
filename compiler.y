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
		
		std::string * nstr = new std::string( *$1 );
		printf("%s", nstr->c_str());
		
		// Declare new Numparser to process Equation
		Compiler::_np = new Numparser();
		
	}
	|
	NUMBER operator number {

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


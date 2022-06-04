%code requires

{
	#include <string>
}

%union
{
	std::string* num_string;
	std::string* func_string;
}

%token <num_string> NUMBER
%token <func_string> FUNCTION
%token ADD SUBTRACT MULTIPLY DIVIDE MODULE EXPONENT SEMICOLON 

%{

#include "compiler.hh"
#include <stdlib.h>
#include "strparse.h"

void yyerror(const char * s);
int yylex();

char ** parse_args(char * func_string);

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
		//printf("\n%s\n", func_str->c_str());
	}
	;

arguments:
	number
	| // Can be blank
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

char ** parse_args(char * func_string) {
	// Creates an array of argument strings from
	// A single string that separates by commas.

	char * temp1 = substr(func_string, indexOf(func_string, '(') + 1);
	char * temp2 = substr(temp1, 0, strlen(temp1) - 1);

	free(temp1);

	char ** args = (char **) malloc(256);
	int num_args = 0;

	for (int i = 0; i < strlen(temp2); i++) {
		if (charAt(temp2, i) == ',') {
			num_args++;
			continue;
		}

		args[num_args][i] = charAt(temp2, i);
	}

	return args;
}

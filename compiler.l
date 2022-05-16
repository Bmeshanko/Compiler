%{

	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include "y.tab.hh"
	int chars = 0;
	int lines = 0;

%}

%option noyywrap

%%

[0-9]* {
	yylval.num_string = new std::string(yytext);
	return NUMBER;
}

"^" {
	return EXPONENT;
}

"*" {
	return MULTIPLY;
}

"/" {
	return DIVIDE;
}

"+" {
	return ADD;
}

"-" {
	return SUBTRACT;
}

"%" {
	return MODULE;
}

";" {
	return SEMICOLON;
}

(.*)[(](.*)[)] {
	// func_string will contain the 
	yylval.func_string = new std::string(yytext);
	return FUNCTION;
}

%%

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: "
			   "compiler <file>\n");
		exit(0);
	}
	
	yyin = fopen(argv[1], "r");

	yyparse();

	//printf("\nThere are %d chars and %d lines\n\n", chars, lines);

	return EXIT_SUCCESS;

}

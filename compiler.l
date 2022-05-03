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

[0-9] {
	return NUMBER;
}

"*" {
	return MULTIPLY;
}

"//" {
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


(print\ ) {
	std::string str = std::string(yytext);
	str = str.substr(5);
	printf("%s\n", str.c_str());
}

%%

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: "
			   "compiler <file>\n");
		exit(0);
	}
	
	yyin = fopen(argv[1], "r");

	yylex();

	//printf("\nThere are %d chars and %d lines\n\n", chars, lines);

	return EXIT_SUCCESS;

}

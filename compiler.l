%{

#include <stdio.h>
#include <stdlib.h>
int chars = 0;
int lines = 0;

%}

%%

[a-zA-Z0-9] {
	chars++;
}

[\n] {
	lines++;
}

%%

int main(int argc, const char ** argv) {
	if (argc != 2) {
		printf("Usage: "
			   "compiler <file>");
		exit(0);
	}
	
	yyin = fopen(argv[1], "r");

	yylex();

	printf("There are %d chars and %d lines", chars, lines);

	return EXIT_SUCCESS;

}

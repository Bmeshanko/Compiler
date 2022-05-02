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

[print][(][^ ][)] {
	std::string str = std::string(yytext);
	printf("%s", str.c_str());
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

	printf("\nThere are %d chars and %d lines\n\n", chars, lines);

	return EXIT_SUCCESS;

}

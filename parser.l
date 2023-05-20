%{

	#include <stdio.h>
	#include <stdlib.h>

%}

DIGIT	[0-9]

%%


"-"?{DIGIT}+ {
	yylval = atoi(yytext);
	return NUM;
}

"+" { return PLS; }
"-" { return MNS; }
"*" { return MLT; }
"/" { return DIV; }
"%" { return MOD; }
"(" { return LPA; }
")" { return RPA; }
"\n" { return NWL; }

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

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
%}

%option noyywrap

DIGIT	[0-9]

%%


"-"?{DIGIT}+ {
	yylval.val = atoi(yytext);
	return NUM;
}

"+" { return PLS; }
"-" { return MNS; }
"*" { return MLT; }
"/" { return DIV; }
"%" { return DIV; }
"&" { return AND; }
"|" { return OR; }
"^" { return XOR; }
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

	return EXIT_SUCCESS;
}

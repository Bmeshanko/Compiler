%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
%}

%option noyywrap

DIGIT	[0-9]

%%

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

"<" { return LTN; }
">" { return GTN; }
">=" { return GEQ; }
"<=" { return LEQ; }
"!=" { return NEQ; }
"==" { return EQU; }

"=" { return DEC; }
"\n" { return NWL; }

"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"{" { return LBR; }
"}" { return RBR; }

"print" { return PRINT; }

[a-zA-Z][a-zA-Z0-9]* {
	yylval.id = strdup(yytext);
	return VAR;
}

"-"?{DIGIT}+ {
	yylval.num = atoi(yytext);
	return NUM;
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

	return EXIT_SUCCESS;
}

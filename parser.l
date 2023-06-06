%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
%}

%option noyywrap

DIGIT	[0-9]

%%

"&&" { return AND; }
"||" { return OR; }

"+" { return PLS; }
"-" { return MNS; }
"*" { return MLT; }
"/" { return DIV; }
"%" { return MOD; }
"&" { return BAND; }
"|" { return BOR; }
"^" { return BXOR; }
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
"while" { return WHILE; }

"void" { return VOID; }
"int" { return INT; }
"return" { return RETURN; }

"{" { return LCB; }
"}" { return RCB; }

"print" { return PRINT; }

"array" { return ARRAY; }
"string" { return STRING; }
"[" { return LSB; }
"]" { return RSB; }

"\t" { return TAB; }

[a-zA-Z][a-zA-Z0-9]* {
	yylval.id = new std::string(yytext);
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

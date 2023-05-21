%union {
	int val;
}

%{
	#include <stdio.h>
	int yyerror (char const *s) {
		return fprintf (stderr, "%s\n", s);
	}
	int yylex (void);
%}

%token PLS MNS MLT DIV MOD
%token AND OR XOR
%token LPA RPA 
%token <val> NUM
%token NWL
%token END

%start Seq
%type <val> Exp

%%

Seq: 
| Seq Line

End: NWL | END

Line: End
| Exp End {
	printf("Hey! %d\n", $1);
}
;

Exp: NUM { $$ = $1; }
| Exp PLS Exp { $$ = $1 + $3; }
| Exp MNS Exp { $$ = $1 - $3; }
| Exp MLT Exp { $$ = $1 * $3; }
| Exp DIV Exp { $$ = $1 / $3; }
| Exp MOD Exp { $$ = $1 % $3; }
| Exp AND Exp { $$ = $1 & $3; }
| Exp OR Exp { $$ = $1 | $3; }
| Exp XOR Exp { $$ = $1 ^ $3; }
| LPA Exp RPA { $$ = $2;};

%%
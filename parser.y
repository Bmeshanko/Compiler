%{
	#include <stdio.h>
	#include "tree.h"
	int yyerror (char const *s) {
		return fprintf(stderr, "%s\n", s);
	}
	int yylex (void);
%}

%union {
	struct Prim * val;
	int num;
}


%token PLS MNS MLT DIV MOD
%token AND OR XOR
%token LPA RPA 
%token <num> NUM
%token NWL
%token END
%start Seq
%type <val> Exp

%%

Seq: 
| Seq Line

Line: NWL
| Exp NWL {
	printf("%s\n", to_string($1));
}
;

Exp: NUM { $$ = new_lit($1); }
| Exp PLS Exp { $$ = new_prim('+', $1, $3); }
| Exp MNS Exp { $$ = new_prim('-', $1, $3); }
| Exp MLT Exp { $$ = new_prim('*', $1, $3); }
| Exp DIV Exp { $$ = new_prim('/', $1, $3); }
| Exp MOD Exp { $$ = new_prim('%', $1, $3); }
| Exp AND Exp { $$ = new_prim('&', $1, $3); }
| Exp OR Exp { $$ = new_prim('|', $1, $3); }
| Exp XOR Exp { $$ = new_prim('^', $1, $3); }
| LPA Exp RPA { $$ = $2; }
;

%%
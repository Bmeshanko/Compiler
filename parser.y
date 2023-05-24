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


%token PLS MNS MLT DIV MOD AND OR XOR LPA RPA 
%token <num> NUM
%token NWL
%start Seq
%type <val> Exp Factor Term Num

%%

Seq: 
| Seq Line

Line: NWL
| Exp NWL { printf("%s\n", prim_to_string($1)); }
;

Factor: NUM { $$ = (struct Prim *)new_lit($1); }
| LPA Exp RPA { $$ = $2; }
;

Term: Factor
| Factor MLT Factor { $$ = new_prim('*', $1, $3); }
| Factor DIV Factor { $$ = new_prim('/', $1, $3); }
| Factor MOD Factor { $$ = new_prim('%', $1, $3); }
;

Num: Term
| Term PLS Term { $$ = new_prim('+', $1, $3); }
| Term MNS Term { $$ = new_prim('-', $1, $3); }
;

Exp: Num
| Num AND Num { $$ = new_prim('&', $1, $3); }
| Num OR Num { $$ = new_prim('|', $1, $3); }
| Num XOR Num { $$ = new_prim('^', $1, $3); }
;

%%
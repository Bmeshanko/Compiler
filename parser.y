%{
	#include <stdio.h>
	#include "tree.h"
	int yyerror (char const *s) {
		return fprintf(stderr, "%s\n", s);
	}
	int yylex (void);
%}

%union {
	struct Prim *val;
	struct Let *dec;
	char * id;
	int num;
}


%token PLS MNS MLT DIV MOD AND OR XOR LPA RPA
%token EQU DEC
%token NWL
%token <id> VAR
%token <num> NUM
%type <val> Exp Factor Term Num
%type <dec> Let
%start Seq

%%

Seq: 
| Seq Line

Line: NWL
| Let NWL { printf("%s\n", let_to_string($1)); }
;

Let: DEC VAR EQU Exp { $$ = new_let($2, $4); }
;

Factor: VAR { $$ = (struct Prim *)new_ref($1); }
| NUM { $$ = (struct Prim *)new_lit($1); } 
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
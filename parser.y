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
%token LTN GTN GEQ LEQ NEQ EQU
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

Let: VAR EQU Exp { $$ = new_let($1, $3); }
;

Factor: VAR { $$ = (struct Prim *)new_ref($1); }
| NUM { $$ = (struct Prim *)new_lit($1); } 
| LPA Exp RPA { $$ = $2; }
;

Term: Factor
| Term MLT Term { $$ = new_prim('*', $1, $3); }
| Term DIV Term { $$ = new_prim('/', $1, $3); }
| Term MOD Term { $$ = new_prim('%', $1, $3); }
;

Num: Term
| Num PLS Num { $$ = new_prim('+', $1, $3); }
| Num MNS Num { $$ = new_prim('-', $1, $3); }
;

Exp: Num
| Exp AND Exp { $$ = new_prim('&', $1, $3); }
| Exp OR Exp { $$ = new_prim('|', $1, $3); }
| Exp XOR Exp { $$ = new_prim('^', $1, $3); }
;

%%
%{
	#include <stdio.h>
	#include "tree.hh"
	int yyerror (char const *s) {
		return fprintf (stderr, "%s\n", s);
	}
	int yylex (void);
%}

%union {
	Tree val;
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
	printf("%s", $1.to_string());
}
;

Exp: NUM { $$ = Lit($1); }
| Exp PLS Exp { $$ = Prim('+', $1, $3); printf("%s", $$.to_string()); }
| Exp MNS Exp { $$ = Prim('-', $1, $3); }
| Exp MLT Exp { $$ = Prim('*', $1, $3); }
| Exp DIV Exp { $$ = Prim('/', $1, $3); }
| Exp MOD Exp { $$ = Prim('%', $1, $3); }
| Exp AND Exp { $$ = Prim('&', $1, $3); }
| Exp OR Exp { $$ = Prim('|', $1, $3); }
| Exp XOR Exp { $$ = Prim('^', $1, $3); }
| LPA Exp RPA { $$ = $2; }
;

%%
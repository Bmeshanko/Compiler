%code requires
{
	#include <string>
}

%{
	#include <stdio.h>
	#include "interpreter.hh"
	#include "parser.hh"
	#include <map>
	int yyerror (char const *s) {
		return fprintf(stderr, "%s\n", s);
	}
	int yylex (void);

	struct Env *env = new_env();
	int line_num = 1;
	// For Untyped AST Interpreter
	std::map<std::string, int> variables;
%}

%union {
	struct Tree *val;
	struct Let *dec;
	struct If *ifs;
	struct While *whiles;
	struct End *end;
	struct Print *print;
	std::string *id;
	int num;
}


%token PLS MNS MLT DIV MOD BAND BOR BXOR LPA RPA AND OR
%token LTN GTN GEQ LEQ NEQ EQU
%token IF WHILE LBR RBR 
%token PRINT
%token NWL TAB
%token DEC
%token <id> VAR
%token <num> NUM
%type <val> Exp Cond Factor Term Num Line
%type <dec> Let
%type <ifs> If
%type <whiles> While
%type <end> End
%type <print> Print
%start Prog

%%

Prog: Seq {
	printf("Un-typed AST:\n");
	printf("---------------------------------\n");
	printf("%s\n", env_to_string(env));
	printf("Interpreter:\n");
	eval(env, 0, env->lines, variables);
}

Seq: 
| Seq Whitespace Line

Whitespace:
| TAB Whitespace

Line: Let NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| If NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| While NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| End NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| Print NWL { env->prog[env->lines++] = (struct Tree *) $1; }
;

If: IF LPA Cond RPA LBR { $$ = new_if($3); }
;

While: WHILE LPA Cond RPA LBR { $$ = new_while($3); }
;

End: RBR { $$ = new_end(); }
;

Let: VAR DEC Cond { $$ = new_let($1, $3); }
;

Print: PRINT LPA Cond RPA { $$ = new_print($3); }

Factor: VAR { $$ = (struct Tree *) new_ref($1); }
| NUM { $$ = (struct Tree *) new_lit($1); } 
| LPA Cond RPA { $$ = $2; }
|
;

Term: Factor
| Term MLT Term { $$ = (struct Tree*) new_prim((char *)"*", $1, $3); }
| Term DIV Term { $$ = (struct Tree*) new_prim((char *)"/", $1, $3); }
| Term MOD Term { $$ = (struct Tree*) new_prim((char *)"%",  $1, $3); }
;

Num: Term
| Num PLS Num { $$ = (struct Tree*) new_prim((char *)"+", $1, $3); }
| Num MNS Num { $$ = (struct Tree*) new_prim((char *)"-", $1, $3); }
;

Exp: Num
| Exp BAND Exp { $$ = (struct Tree*) new_prim((char *)"&", $1, $3); }
| Exp BOR Exp { $$ = (struct Tree*) new_prim((char *)"|", $1, $3); }
| Exp BXOR Exp { $$ = (struct Tree*) new_prim((char *)"^", $1, $3); }
| Exp LTN Exp { $$ = (struct Tree*) new_prim((char *)"<", $1, $3); }
| Exp GTN Exp { $$ = (struct Tree*) new_prim((char *)">", $1, $3); }
| Exp LEQ Exp { $$ = (struct Tree*) new_prim((char *)"<=", $1, $3); }
| Exp GEQ Exp { $$ = (struct Tree*) new_prim((char *)">=", $1, $3); }
| Exp NEQ Exp { $$ = (struct Tree*) new_prim((char *)"!=", $1, $3); }
| Exp EQU Exp { $$ = (struct Tree*) new_prim((char *)"==", $1, $3); }
;

Cond: Exp
| Cond AND Cond { $$ = (struct Tree*) new_prim((char *)"&&", $1, $3); }
| Cond OR Cond { $$ = (struct Tree*) new_prim((char *)"||", $1, $3); }
;

%%
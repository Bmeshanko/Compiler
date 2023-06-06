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
	std::map<std::string, int *> variables;
%}

%union {
	struct Tree *val;
	struct Let *let;
	struct Array *array;
	struct If *ifs;
	struct While *whiles;
	struct Fun *fun;
	struct App *app;
	struct Return *returns;
	struct End *end;
	struct Print *print;
	std::string *id;
	int num;
}

%token PLS MNS MLT DIV MOD BAND BOR BXOR LPA RPA AND OR
%token LTN GTN GEQ LEQ NEQ EQU
%token IF WHILE LCB RCB
%token INT CHAR VOID RETURN
%token PRINT
%token LSB RSB
%token NWL TAB
%token DEC
%token <id> VAR
%token <num> NUM
%type <val> Exp Cond Factor Term Num Line
%type <let> VarLet ArrayLet
%type <array> ArrayInit
%type <ifs> If
%type <whiles> While
%type <fun> Void Int
%type <app> App
%type <end> End
%type <returns> Return
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

Line: Let NWL 
| ArrayInit NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| If NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| While NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| Fun NWL 
| App NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| Return NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| End NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| Print NWL { env->prog[env->lines++] = (struct Tree *) $1; }
| NWL
;

If: IF LPA Cond RPA LCB { $$ = new_if($3); }

While: WHILE LPA Cond RPA LCB { $$ = new_while($3); }

Fun: Void { env->prog[env->lines++] = (struct Tree *) $1; }
| Int { env->prog[env->lines++] = (struct Tree *) $1; }

Void: VOID VAR LPA RPA LCB { $$ = new_fun($2, true); }

Int: INT VAR LPA RPA LCB { $$ = new_fun($2, false); }

App: VAR LPA RPA { $$ = new_app($1, true); }

Return: RETURN Cond { $$ = new_return($2); }

End: RCB { $$ = new_end(); }

Let: VarLet { env->prog[env->lines++] = (struct Tree *) $1; }
| ArrayLet { env->prog[env->lines++] = (struct Tree *) $1; }

VarLet: INT VAR DEC Cond { $$ = new_let($2, (struct Tree *) new_lit(0), $4, 0); }
| CHAR VAR DEC Cond { $$ = new_let($2, (struct Tree *) new_lit(0), $4, 1); }

ArrayLet: VAR LSB Cond RSB DEC Cond { $$ = new_let($1, $3, $6, 0); }

ArrayInit: INT VAR LSB Cond RSB { $$ = new_array($2, $4, 0); }
| CHAR VAR LSB Cond RSB { $$ = new_array($2, $4, 1); }

Print: PRINT LPA Cond RPA { $$ = new_print($3); }

Factor: VAR { $$ = (struct Tree *) new_ref($1, (struct Tree *) new_lit(0)); }
| VAR LSB Cond RSB { $$ = (struct Tree *) new_ref($1, $3); }
| NUM { $$ = (struct Tree *) new_lit($1); } 
| LPA Cond RPA { $$ = $2; }
| VAR LPA RPA { $$ = (struct Tree *) new_app($1, false); }
|

Term: Factor
| Term MLT Term { $$ = (struct Tree*) new_prim((char *)"*", $1, $3); }
| Term DIV Term { $$ = (struct Tree*) new_prim((char *)"/", $1, $3); }
| Term MOD Term { $$ = (struct Tree*) new_prim((char *)"%",  $1, $3); }

Num: Term
| Num PLS Num { $$ = (struct Tree*) new_prim((char *)"+", $1, $3); }
| Num MNS Num { $$ = (struct Tree*) new_prim((char *)"-", $1, $3); }

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

Cond: Exp
| Cond AND Cond { $$ = (struct Tree*) new_prim((char *)"&&", $1, $3); }
| Cond OR Cond { $$ = (struct Tree*) new_prim((char *)"||", $1, $3); }

%%
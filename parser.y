%union {
	double res;
}

%{
	#include <stdio.h>
	#define YYSTYPE double
	int yyerror (char const *s);
	extern int yylex (void);
%}

%token PLS MNS MLT DIV MOD
%token LPA RPA 
%token NUM
%token NWL
%start Seq
%type <res> Exp

%%
Seq: 
| Seq Line

Line: NWL
| Exp NWL
;

Exp: NUM {
	$$ = $1;
}
|
Exp PLS Exp {
	$$ = $1 + $3;
}
|
Exp MNS Exp {
	$$ = $1 - $3;
}
|
Exp MLT Exp {
	$$ = $1 - $3;
}
|
Exp DIV Exp {
	$$ = $1 - $3;
}
|
Exp MOD Exp {
	$$ = $1 - $3;
}
|
LPA Exp RPA {
	$$ = $2;
};

%%

void yyerror(const char * s) {
	fprintf(stderr, "%s", s);
}
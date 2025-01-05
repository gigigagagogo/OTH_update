%{
  #include <stdio.h>
  #include <math.h>
  int yydebug = 0;
  extern int yylineno;
  int yylex (void);
  void yyerror(const char *msg);
  int vars[256];
%}

%define parse.error verbose

%union {
     int nr;
     char *str;
}

%type  <nr> TERM
%token <nr> num
       <str> id
	add
	mul
	division
	ele
	egu
	sub
%right egu
%left sub add
%left  mul division
%right ele

%start START

%%

START: START TERM ';' { printf("R: %d\n", $2); }
     | %empty

TERM: TERM sub TERM { $$ = $1 - $3; }
    | TERM add TERM { $$ = $1 + $3; }
    | TERM mul TERM { $$ = $1 * $3; }
    | TERM division TERM { $$ = $1 / $3; }
    | TERM ele TERM { $$ = pow($1, $3); }
    | id egu TERM   { $$ = $3; vars[(int)$1[0]] = $3; }
    | num /* default action: $$ = $1 */
    | id { $$ = vars[(int)$1[0]]; }

%%

void yyerror(const char *msg) {
  printf("Error line %d: %s\n", yylineno, msg);
}

int main (void) {
  yyparse();

  return 0;
}

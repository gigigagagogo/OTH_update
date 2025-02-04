%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include "types.h"
    #include "parser.tab.h"
    
    // Buffer to accumulate multi-character strings
    char *current_string = NULL;

    // Reset the string buffer
    void reset_string_buffer() {
        if (current_string) {
            free(current_string);
            current_string = NULL;
        }
    }

    // Append fragments to the string buffer
    void append_to_string(const char *fragment) {
        if (!current_string) {
            current_string = strdup(fragment);
        } else {
            size_t len = strlen(current_string) + strlen(fragment) + 1;
            current_string = realloc(current_string, len);
            if (!current_string) {
                printf("Error: Memory allocation failed in append_to_string\n");
                exit(EXIT_FAILURE);
            }
            strcat(current_string, fragment);
        }
    }
%}

	/* Regular expression definitions */
DIGIT [0-9]+
OPERATOR [+-/!<>]

	/* Define states for handling strings and comments */
%x STRING COMMENT

	/* Flex options */
%option noinput nounput noyywrap yylineno 

%%

	/* Keywords */
"imagine"       { return T_IMAGINE; }
"nah"           { return T_NAH; }
"one_by_one"    { return T_ONE_BY_ONE; }
"as_long_as"    { return T_AS_LONG_AS; }
"go"            { return T_GO; }
"all_set"       { return T_ALL_SET; }
"throw_up"      { return T_THROWUP; }

	/* Operators */
"+"             { return T_PLUS; }
"-"             { return T_MINUS; }
"*"             { return T_MULTIPLY; }
"/"             { return T_DIVIDE; }
"->"            { return T_FAI; }
"-->"           { return T_EQUAL; }
"!->"           { return T_NEQUAL; }
">="            { return T_GEQUAL; }
"<="            { return T_LEQUAL; }
"<"             { return T_LESS; }
">"             { return T_GREATER; }
"&&"            { return T_AND; }
"||"            { return T_OR; }

	/* Other language-specific tokens */
"send_back"     { return T_SENDBACK; }
"in"            { return T_IN; }
"a_new_one"     { return T_A_NEW_ONE; }
"("             { return T_LPAREN; }
")"             { return T_RPAREN; }
"{"             { return T_LCURPAR; }
"}"             { return T_RCURPAR; }
","             { return T_COMMA; }

	/* Data types */
"zip"           { return T_ZIP_TYPE; }
"whole_y"       { return T_WHOLEY_TYPE; }
"floaty"        { return T_FLOATY_TYPE; }  
"chain"         { return T_STRING_TYPE; }

	/* Built-in functions */
"rando"         { return T_RANDO; }
"gimme"         { return T_GIMME; }
"size_up"       { return T_SIZE_UP; }
"join_in"       { return T_JOIN_IN; }

	/* Ignore whitespace and newlines */
"\n"            { }
" "             { }
"\t"            { }

	/* Numeric literals */
{DIGIT}"."{DIGIT}  { yylval.fnum = atof(yytext); return T_FLOATY; }
{DIGIT}           { yylval.num = atoi(yytext); return T_WHOLEY; }

	/* String handling */
"\^"             { BEGIN(STRING); reset_string_buffer(); }
<STRING>[^\\^]+  { append_to_string(yytext); }
<STRING>"\\gms"  { append_to_string("\n"); }
<STRING>"\\so"   { append_to_string("\t"); }
<STRING>"\^"     { 
                    if (!current_string) {
                        yylval.str = strdup(""); 
                    } else {
                        yylval.str = strdup(current_string);
                    }
                    reset_string_buffer();
                    BEGIN(INITIAL);
                    return T_STRING;
                }

	/* Comment handling */
"x\$"            { BEGIN(COMMENT); }
<COMMENT>[^\$]+  { ; }
<COMMENT>"\$x"   { BEGIN(INITIAL); }

	/* Identifiers */
[a-zA-Z][_a-zA-Z0-9]* { yylval.id = strdup(yytext); return T_IDENTIFIER; }

	/* Unknown characters */
[^ ^\n^\t]{1}   { return yytext[0]; }

%%


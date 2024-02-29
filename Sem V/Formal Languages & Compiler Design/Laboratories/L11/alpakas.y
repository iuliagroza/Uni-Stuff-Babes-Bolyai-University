
%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yylineno;
extern char* yytext;

void yyerror(const char *s);
%}

%token IDENTIFIER POSITIVE_NUMBER
%left '-' '+'
%left '*' '/'

%%

program : statement
        | statement program
        ;

statement : var_statement ';'
          | arr_statement ';'
          | assign_statement ';'
          | if_statement
          | while_statement
          | return_statement ';'
          | function_call_statement ';'
          ;

var_statement : "var" identifier_list
              ;

arr_statement : "arr" '[' POSITIVE_NUMBER ']' pure_identifier_list
              ;

assign_statement : IDENTIFIER '=' expression
                 ;

if_statement : "if" '(' condition ')' '{' program '}'
             | "if" '(' condition ')' '{' program '}' "else" '{' program '}'
             ;

while_statement : "while" '(' condition ')' '{' program '}'
                ;

return_statement : "return" expression
                 ;

function_call_statement : IDENTIFIER '(' argument_list ')'
                        ;

identifier_list : IDENTIFIER
                | IDENTIFIER ',' identifier_list
                ;

pure_identifier_list : IDENTIFIER
                     | IDENTIFIER ',' pure_identifier_list
                     ;

expression : IDENTIFIER
           | POSITIVE_NUMBER
           | expression '+' expression
           | expression '-' expression
           | expression '*' expression
           | expression '/' expression
           ;

condition : expression '<' expression
          | expression '>' expression
          | expression "==" expression
          | expression "!=" expression
          | expression "<=" expression
          | expression ">=" expression
          ;

argument_list : /* empty */
              | expression
              | expression ',' argument_list
              ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int main(void) {
    if (yyparse()) {
        printf("Parsing failed\n");
    } else {
        printf("Parsing succeeded\n");
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#ifdef _WIN32
#include <string.h>
static char buffer[2048];
char* readline(char* prompt){
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy= malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[(strlen(cpy))-1]='\0';
	return cpy;

}

void add_history(char* unused){} //not implemented and not gonna do it
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif
int main(int argc, char** argv) {

mpc_parser_t* Number=mpc_new("number");
mpc_parser_t* Operator=mpc_new("operator");
mpc_parser_t* PrefExpression=mpc_new("prefexpression");
mpc_parser_t* Prefix=mpc_new("prefix");
mpc_parser_t* InfExpression=mpc_new("infexpression");
mpc_parser_t* Infix=mpc_new("infix");
mpc_parser_t* Lispy=mpc_new("lispy");
//infix is not working entirely regarding parsing long expressions with brackets
  mpca_lang(MPCA_LANG_DEFAULT,
        " \
        number   : /-?[0-9]+(\\.[0-9]+)?/ ; \
        operator : '+' | '-' | '*' | '/' | '%' | \"add\" | \"sub\" | \"mul\" | \"div\" | \"mod\"; \
        prefexpression : <number> | '(' <operator> <prefexpression>+ ')' ; \
        prefix : <operator> <prefexpression>+ ; \
        infexpression : <number> | '(' <infexpression> <operator> <infexpression> ')' ; \
        infix : <infexpression> (<operator> <infexpression>)+ ; \
        lispy: /^/  <infix> | <prefix>  /$/ ; \
        ",
        Number, Operator, PrefExpression, Prefix, InfExpression, Infix, Lispy);


puts("Lispy Version 0.0.0.0.2");
puts("Stage: Prefix & Infix Notation Parser");
puts("Press Ctrl+C to Exit\n");

while (1) {
    char* input=readline("lispy> ");
    add_history(input);
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
        mpc_ast_print(r.output);
        mpc_ast_delete(r.output);
}
    else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
}
free(input);
input = NULL;
}
mpc_cleanup(7, Number, Operator, PrefExpression, Prefix, InfExpression, Infix, Lispy);

return 0;
}

// File: main.c
// Author: CJ Taylor

#include <stdio.h>
#include <polite.h>

#include "lexer/lexer.h"

static char* src = "int main() {\nreturn 1;\n}";

int main(int argc, char** argv) {

	Token* tokens = tokenize(src);

	while (tokens != NULL) {
		printf("token: %s, count: %d\n", tokens->value, tokens->count);

		tokens = tokens->next;
	}

	return 0;
}

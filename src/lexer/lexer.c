// File: lexer.c
// Author: CJ Taylor

// For simplicity made with no global state

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "lexer.h"

static const KeywordMap keywords[] = {
	{"if", TOK_IF}, {"elif", TOK_ELIF}, {"else", TOK_ELSE},
	{"return", TOK_RETURN}, {"for", TOK_FOR}, {"while", TOK_WHILE}, 
	{"break", TOK_BREAK}, {"continue", TOK_CONTINUE}, {"struct", TOK_STRUCT},
	{"enum", TOK_ENUM}, {"true", TOK_TRUE}, {"false", TOK_FALSE}, 
	{"const", TOK_CONST}, {"alloc", TOK_ALLOC}, {"free", TOK_FREE},
	{"cast", TOK_CAST}, {"sizeof", TOK_SIZEOF}, {"defer", TOK_DEFER},
	{"switch", TOK_SWITCH}, {"in", TOK_IN}, {"int", TOK_INT}, 
	{"char", TOK_CHAR}, {"float", TOK_FLOAT}, {"double", TOK_DOUBLE},
	{"long", TOK_LONG}, {"bool", TOK_BOOL} 
};

static const size_t keywords_size = sizeof(keywords) / sizeof(keywords[0]);

static Token* list;
static Token* head;

void init_lexer() {
	++list->count;
}

void lexer_push(TokenType ty, char* value) {
	Token* new = (Token *) malloc(sizeof(Token));
	list->next = new;
	new->prev = list;
	new->ty = ty;
	new->value = strdup(value);
	new->next = NULL;
	new->count = list->count + 1;
	list = new;
}

static TokenType match_keywords(char* val) {
	for (size_t i = 0; i < keywords_size; ++i) {
		if (strcmp(keywords[i].text, val) == 0) {
			return keywords[i].ty;
		}
	}
	return TOK_IDENT;
}

Token* tokenize(char* src) {
	list = (Token *) malloc(sizeof(Token));
	head = list;
	bzero(list, sizeof(Token));

	size_t len = strlen(src);
	for (size_t i = 0; i < len; ++i) {
		char c = src[i];

		if (isspace(c)) {
			continue;
		}

		switch (c) {
			case '(':
				lexer_push(TOK_LPAREN, "(");
				break;
			case ')':
				lexer_push(TOK_RPAREN, ")");
				break;
			case '{':
				lexer_push(TOK_LBRACE, "{");
				break;
			case '}':
				lexer_push(TOK_RBRACE, "}");
				break;
			case '[':
				lexer_push(TOK_LBRACKET, "[");
				break;
			case ']':
				lexer_push(TOK_RBRACKET, "]");
				break;
			case ';':
				lexer_push(TOK_SEMICOLON, ";");
				break;
			case ',':
				lexer_push(TOK_COMMA, ",");
				break;
			case '.':
				lexer_push(TOK_DOT, ".");
				break;
			case '@':
				lexer_push(TOK_AT, "@");
				break;
			case '=':
				if (src[i+1] == '=') {
					lexer_push(TOK_EQEQ, "==");
					++i;
				} else {
					lexer_push(TOK_EQUAL, "=");
				}
				break;
			case '+':
				lexer_push(TOK_PLUS, "+");
				break;
			case '-':
				lexer_push(TOK_MINUS, "-");
				break;
			case '*':
				lexer_push(TOK_STAR, "*");
				break;
			case '/':
				lexer_push(TOK_SLASH, "/");
				break;
			case '>':
				if (src[i+1] == '>') {
					lexer_push(TOK_LE, ">=");
					++i;
				} else {
					lexer_push(TOK_LT, ">");
				}
				break;
		}

		if (c == '"') {
			char* ptr = &src[i];
			size_t len = i;
			++i;
			c = src[i];

			while (c != '"') {
				++i;
				c = src[i];
			}
			len = i - len;
			char* value = malloc(sizeof(char) * (len + 1));
			strncpy(value, ptr, len);
			value[len] = '\0';
			lexer_push(TOK_STRING_LIT, value);
		}

		if (isalpha(c)) {
			char* ptr = &src[i];
			size_t len = i;
			++i;
			c = src[i];

			while (isalnum(c) || c == '_') {
				++i;
				c = src[i];
			}
			len = i - len;
			char* value = malloc(sizeof(char) * (len + 1));
			strncpy(value, ptr, len);
			value[len] = '\0';
			TokenType x = match_keywords(value);
			if (x == TOK_ERROR) {
				lexer_push(x, "error");
			} else {
			lexer_push(x, value);
			}
			free(value);
			--i;
		}


		if (isdigit(c)) {
			char* ptr = &src[i];
			size_t len = i;
			++i;
			c = src[i];

			while (isdigit(c)) {
				++i;
				c = src[i];
			}
			len = i - len;
			char* value = malloc(sizeof(char) * (len + 1));
			strncpy(value, ptr, len);
			value[len] = '\0';
			lexer_push(TOK_INT_LIT, value);
			free(value);
			--i;
		}
		if (c == '\0') {
			lexer_push(TOK_EOF, "eof");
		}
	}
return head;
}

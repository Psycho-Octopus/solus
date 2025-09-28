#pragma once

// File: lexer.h
// Author: CJ Taylor

typedef enum {
	TOK_EOF,
	TOK_ERROR,
	TOK_IDENT,
	TOK_SYMBOL,
	TOK_PROGRAM,
	TOK_WHITESPACE,

  	// Literals
	TOK_INT_LIT,
	TOK_CHAR_LIT,
	TOK_FLOAT_LIT,
	TOK_DOUBLE_LIT,
	TOK_LONG_LIT,
	TOK_STRING_LIT,

  	// Keywords
  	TOK_IF,
	TOK_ELIF,
	TOK_ELSE,
	TOK_RETURN,
	TOK_FOR,
	TOK_WHILE,
	TOK_BREAK,
	TOK_CONTINUE,
	TOK_STRUCT,
	TOK_ENUM,
	TOK_TRUE,
	TOK_FALSE,
	TOK_CONST,
	TOK_ALLOC,
	TOK_FREE,
	TOK_CAST,
	TOK_SIZEOF,
	TOK_DEFER,
	TOK_SWITCH,
	TOK_IN,

	// Type anotation keywords
	TOK_INT,
	TOK_CHAR,
	TOK_FLOAT,
	TOK_DOUBLE,
	TOK_LONG,
	TOK_BOOL,

	// Preprocessor directives
	TOK_IMPORT,
	TOK_DEFINE,
	TOK_USE,

  	// Symbols
	TOK_SYMBOLS,
	TOK_LPAREN, 		// (
	TOK_RPAREN, 		// )
	TOK_LBRACE,			// {
	TOK_RBRACE,		    // }
	TOK_LBRACKET,       // [
	TOK_RBRACKET,       // ]
	TOK_SEMICOLON,      // ;
	TOK_COMMA,			// ,
	TOK_DOT,			// .
	TOK_AT,				// @
	TOK_EQUAL,			// =
	TOK_PLUS,			// +
	TOK_MINUS,			// -
	TOK_STAR,			// *
	TOK_SLASH,			// /
	TOK_LT,				// >
	TOK_GT,				// <
	TOK_LE,				// >=
	TOK_GE,				// <=
	TOK_EQEQ,			// ==
	TOK_NEQ,			// !=
    TOK_AMP,         	// &
  	TOK_PIPE,        	// |
  	TOK_CARET,       	// ^
  	TOK_TILDE,       	// `
  	TOK_AND,         	// &&
  	TOK_OR,          	// || 
  	TOK_RESOLVE,     	// ::
  	TOK_COLON,       	// : 
  	TOK_BANG,        	// !
	TOK_QUESTION,    	// ?
  	TOK_PLUSPLUS,    	// ++
  	TOK_MINUSMINUS,  	// --
  	TOK_SHIFT_LEFT,  	// <<
  	TOK_SHIFT_RIGHT, 	// >
  	TOK_RANGE,       	// ..
  	TOK_RIGHT_ARROW, 	// =>
  	TOK_MODL,        	// %
	TOK_UNDERSCORE		// _
} TokenType;

typedef struct token_t {
	TokenType ty;
	char* value;
	int count;
	struct token_t* next;
	struct token_t* prev;
} Token;

typedef struct {
	char* text;
	TokenType ty;
} KeywordMap;

typedef struct {
  const char* text;
  TokenType ty; 
} SymbolMap;


Token* tokenize(char *src);

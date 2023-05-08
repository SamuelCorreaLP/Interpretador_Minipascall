#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>

enum TokenType{
	//Specials
	TT_UNEXPECTED_EOF = -2,
	TT_INVALID_TOKEN  = -1,
	TT_END_OF_FILE    =  0,

	//Symbols
	TT_SEMICOLON,         // ;
	TT_ASSIGN,            // :=
	TT_COLON,             // :
	TT_OPEN_PARENTESIS,   //(
	TT_CLOSE_PARENTHESIS, //)
	TT_DOT,               //.
	TT_COMMA,             //,

	//Logic operator
	TT_EQUAL,             // =
	TT_NOT_EQUAL,         // <>
	TT_LOWER,             // <
	TT_LOWER_EQUAL,       // <=
	TT_GREATER,           // >
	TT_GREATER_EQUAL,     // >=
	TT_NOT,               // not
	TT_AND,               //and
	TT_OR,                //or

	//Arithmetic operators
	TT_ADD,               // +
	TT_SUB,               // -
	TT_MUL,               // *
	TT_DIV,               // /
	TT_MOD,               // %

	//Keywords
	TT_PROGRAM,           //program
	TT_CONSTANT,          //const
	TT_VARIABLE,          //var
	TT_BEGIN,             //begin
	TT_END,               //end
	TT_REPEAT,            //repeat
	TT_UNTIL,             //until
	TT_WRITE,             //write
	TT_WRITE_LN,          //writeln
	TT_READ_LN,           //readln
	TT_IF,                //if
	TT_THEN,              //then
	TT_ELSE,              //else
	TT_CASE,              //case
	TT_OF,                //of
	TT_WHILE,             //while
	TT_DO,                //do
	TT_FOR,               //for
	TT_TO,                //to

	//Others
	TT_NUMBER,            // number
	TT_FLOAT,             // ponto flutuante
	TT_STRING,            // string
	TT_VAR                // variable

};

inline std::string tt2str(enum TokenType type){
	switch(type){
		//Specials
		case TT_UNEXPECTED_EOF:
			return "UNEXPECTED_EOF";
		case TT_INVALID_TOKEN:
			return "INVALID_TOKEN";
		case TT_END_OF_FILE:
			return "END_OF_FILE";

		//Symbols
		case TT_SEMICOLON:
			return "SEMICOLON";
		case TT_ASSIGN:
			return "ASSIGN";
		case TT_COLON:
			return ":";
		case TT_OPEN_PARENTESIS:
			return "OPEN_PARENTESIS";
		case TT_CLOSE_PARENTHESIS:
			return "CLOSE_PARENTHESI";
		case TT_DOT:
			return "DOT";
		case TT_COMMA:
			return "COMMA";

		//Logic operator
		case TT_EQUAL:
			return "EQUAL";
		case TT_NOT_EQUAL:
			return "NOT_EQUAL";
		case TT_LOWER:
			return "LOWER";
		case TT_LOWER_EQUAL:
			return "LOWER_EQUAL";
		case TT_GREATER:
			return "GREATER";
		case TT_GREATER_EQUAL:
			return "GREATER_EQUAL";
		case TT_NOT:
			return "NOT";
		case TT_AND:
			return "AND";
		case TT_OR:
			return "OR";

		//Arithmetic operators
		case TT_ADD:
			return "ADD";
		case TT_SUB:
			return "SUB";
		case TT_MUL:
			return "MUL";
		case TT_DIV:
			return "DIV";
		case TT_MOD:
			return "MOD";

		//Keywords
		case TT_PROGRAM:
			return "PROGRAM";
		case TT_CONSTANT:
			return "CONSTANT";
		case TT_VARIABLE:
			return "VARIABLE";
		case TT_BEGIN:
			return "BEGIN";
		case TT_END:
			return "END";
		case TT_REPEAT:
			return "REPEAT";
		case TT_UNTIL:
			return "UNTIL";
		case TT_WRITE:
			return "WRITE";
		case TT_WRITE_LN:
			return "WRITE_LN";
		case TT_READ_LN:
			return "READ_LN";
		case TT_IF:
			return "IF";
		case TT_THEN:
			return "THEN";
		case TT_ELSE:
			return "ELSE";
		case TT_CASE:
			return "CASE";
		case TT_OF:
			return "OF";
		case TT_WHILE:
			return "WHILE";
		case TT_DO:
			return "DO";
		case TT_FOR:
			return "FOR";
		case TT_TO:
			return "TO";

		//Others
		case TT_NUMBER:
			return "NUMBER";
		case TT_FLOAT:
			return "FLOAT";
		case TT_STRING:
			return "STRING";
		case TT_VAR:
			return "VAR";

		default:
			throw std::string("invalid token type");
	}
}
#endif

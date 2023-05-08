#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <list>

#include "SyntaticAnalysis.h"
#include "../interpreter/util/Memory.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
	m_lex(lex), m_current(lex.nextToken()) {

	}
SyntaticAnalysis::~SyntaticAnalysis() {

}

Command*  SyntaticAnalysis::start() {
	Command* cmd = procProgram();
	eat(TT_END_OF_FILE);
	return cmd;
}

void SyntaticAnalysis::advance() {
	m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
	//std::cout << "Expected (..., " << tt2str(type)
	//         <<  "), found (\"" + m_current.token << "\", "
	// 		   << tt2str(m_current.type) << ")" << std::endl;
	if (type == m_current.type) {
		advance();
	} else {
		showError();
	}
}

void SyntaticAnalysis::showError() {
	std::cout << std::setw(2) << std::setfill('0') << m_lex.line() << ": ";

	switch (m_current.type) {
		case TT_INVALID_TOKEN:
			std::cout << "Lexema inválido [" << m_current.token << "]" << std::endl;
			break;
		case TT_UNEXPECTED_EOF:
		case TT_END_OF_FILE:
			std::cout << "Fim de arquivo inesperado" << std::endl;
			break;
		default:
			std::cout << "Lexema não esperado [" << m_current.token << "]" << std::endl;
			break;
	}

    exit(1);
}

// <program>  ::= program <id> ';'
//            [ const <const> { <const> } ]
//            [ var <var> { <var> } ]
//            <block> '.'
Command* SyntaticAnalysis::procProgram() {
	eat(TT_PROGRAM);
	procId();
	eat(TT_SEMICOLON);
	if(m_current.type == TT_CONSTANT) {
		advance();
		procConst();
		while (m_current.type == TT_VAR){
			procConst();
		}
	}
	if(m_current.type == TT_VARIABLE) {
		advance();
		procVar();
		while (m_current.type == TT_VAR){
			procVar();
		}
	}
	Command* cmd = procBody();
	eat(TT_DOT);
	return cmd;
}

// <const>    ::= <id> '='<value> ';'
void SyntaticAnalysis::procConst() {
	Variable* var = procId();
	std::string name = var->getName();
	eat(TT_EQUAL);
	Type* value = procValue();
	eat(TT_SEMICOLON);
	Memory::registryConstant(name, value);
}

// <var>      ::= <id> { ',' <id> } [ '='<value> ] ';'
void SyntaticAnalysis::procVar() {

	Variable* var;
	std::string name;
	Type* value = 0;

	var = procId();
	name = var->getName();

	if(m_current.type == TT_COMMA) {
		Memory::registryVariable(name, value);
	}

	while(m_current.type == TT_COMMA) {
		advance();
		var = procId();
		name = var->getName();
		Memory::registryVariable(name, value);
	}
	if(m_current.type == TT_EQUAL) {
		advance();
		value = procValue();
		Memory::registryVariable(name, value);
	}
	eat(TT_SEMICOLON);
}

// <body>     ::= <block> | <cmd>
Command* SyntaticAnalysis::procBody() {
	Command* cmd;
	if(m_current.type == TT_BEGIN) {
		cmd = procBlock();
	} else {
		cmd = procCmd();
	}
	return cmd;
}

// <block>    ::=begin[ <cmd> { ';' <cmd> } ] end
BlocksCommand* SyntaticAnalysis::procBlock() {
	eat(TT_BEGIN);
	int line = m_lex.line();
	BlocksCommand* block = new BlocksCommand(line);
	if(m_current.type == TT_IF || m_current.type == TT_CASE || m_current.type == TT_WHILE ||
	    m_current.type == TT_FOR || m_current.type == TT_REPEAT || m_current.type == TT_WRITE ||
		m_current.type == TT_WRITE_LN || m_current.type == TT_READ_LN ||m_current.type == TT_VAR) {
			Command* cmd = procCmd();
			block->addCommand(cmd);
			while(m_current.type == TT_SEMICOLON){
				advance();
				cmd = procCmd();
				block->addCommand(cmd);
			}
	}
	eat(TT_END);
	return block;
}

// <cmd>      ::= <assign> | <if> | <case> | <while> | <for> | <repeat> | <write> | <read>
Command* SyntaticAnalysis::procCmd() {
	Command* cmd;
	if(m_current.type == TT_READ_LN){
		cmd = procRead();
	} else if(m_current.type == TT_IF){
		cmd = procIf();
	} else if(m_current.type == TT_CASE){
		cmd = procCase();
	} else if(m_current.type == TT_WHILE){
		cmd = procWhile();
	} else if(m_current.type == TT_FOR){
		cmd = procFor();
	} else if(m_current.type == TT_REPEAT){
		cmd = procRepeat();
	} else if(m_current.type == TT_WRITE || m_current.type == TT_WRITE_LN){
		cmd = procWrite();
	} else if(m_current.type == TT_VAR) {
		cmd = procAssing();
	} else {
		showError();
	}
	return cmd;
}

// <assign>   ::= <id> ':='<expr>
AssignCmd* SyntaticAnalysis::procAssing() {
	Variable* var = procId();
	eat(TT_ASSIGN);
	Expr* expr = procExpr();
	int line = m_lex.line();
	AssignCmd* cmd = new AssignCmd(line, var, expr);
	return cmd;
}

// <if>       ::= if <boolexpr> then <body> [else<body>]
IfCommand* SyntaticAnalysis::procIf() {
	int line = m_lex.line();
	eat(TT_IF);
	BoolExpr* boolexpr = procBooleanexpr();
	eat(TT_THEN);
	Command* thencmd = procBody();
	IfCommand* ifcmd = new IfCommand(line, boolexpr, thencmd);
	if(m_current.type == TT_ELSE){
		advance();
		Command* elsecmd = procBody();
		ifcmd->setElseCommands(elsecmd);
	}
	return ifcmd;
}

// <case>     ::= case<expr> of{ <value> ':'<body> ';' } [ else<body> ';' ] end
CaseCommand* SyntaticAnalysis::procCase() {
	eat(TT_CASE);
	int line = m_lex.line();
	Expr* expr = procExpr();
	CaseCommand* casecmd = new CaseCommand(line, expr);
	eat(TT_OF);
	while(m_current.type == TT_NUMBER || m_current.type == TT_FLOAT || m_current.type == TT_STRING) {
		Type* value = procValue();
		eat(TT_COLON);
		Command* cmd = procBody();
		eat(TT_SEMICOLON);
		casecmd->addOption(value, cmd);
	}
	if(m_current.type == TT_ELSE) {
		advance();
		Command* elsecmd = procBody();
		eat(TT_SEMICOLON);
		casecmd->setOtherwise(elsecmd);
	}
	eat(TT_END);
	return casecmd;
}

// <while>    ::= while <boolexpr> do <body>
WhileCommand* SyntaticAnalysis::procWhile() {
	eat(TT_WHILE);
	int line = m_lex.line();
	BoolExpr* boolexpr = procBooleanexpr();
	eat(TT_DO);
	Command* cmd = procBody();
	WhileCommand* whilecmd = new WhileCommand(line, boolexpr, cmd);
	return whilecmd;
}

// <repeat>   ::= repeat[ <cmd> { ';' <cmd> } ] until<boolexpr>
RepeatCommand* SyntaticAnalysis::procRepeat() {
	int line = m_lex.line();
	std::list<Command*> cmdlist;
	Command* cmd;
	eat(TT_REPEAT);
	if(m_current.type == TT_IF || m_current.type == TT_CASE || m_current.type == TT_WHILE ||
	    m_current.type == TT_FOR || m_current.type == TT_REPEAT || m_current.type == TT_WRITE ||
		m_current.type == TT_WRITE_LN || m_current.type == TT_READ_LN ||m_current.type == TT_VAR) {
			cmd = procCmd();
			cmdlist.push_back(cmd);
			while(m_current.type == TT_SEMICOLON) {
				advance();
				cmd = procCmd();
				cmdlist.push_back(cmd);
			}
	}
	eat(TT_UNTIL);
	BoolExpr* boolexpr = procBooleanexpr();
	RepeatCommand* repeat = new RepeatCommand(line, cmdlist, boolexpr);
	return repeat;
}

// <for>      ::= for<id> ':='<expr> to<expr> do<body>
ForCommand* SyntaticAnalysis::procFor() {
	int line = m_lex.line();
	eat(TT_FOR);
	Variable* id = procId();
	eat(TT_ASSIGN);
	Expr* src = procExpr();
	eat(TT_TO);
	Expr* dst = procExpr();
	eat(TT_DO);
	Command* cmd =  procBody();
	ForCommand* forcmd = new ForCommand(line, id, src, dst, cmd);
	return forcmd;
}

// <write>    ::= (write| writeln) '(' [ <expr> { ',' <expr> } ] ')'
WriteCommand* SyntaticAnalysis::procWrite() {
	int line = m_lex.line();
	bool ln;
	Expr* expr;
	if(m_current.type == TT_WRITE){
		eat(TT_WRITE);
		ln = true;
	} else{
		eat(TT_WRITE_LN);
		ln = false;
	}
	WriteCommand* write = new WriteCommand(line, ln);
	eat(TT_OPEN_PARENTESIS);
	if(m_current.type == TT_NUMBER || m_current.type == TT_FLOAT || m_current.type == TT_STRING ||
	    m_current.type == TT_VAR || m_current.type == TT_OPEN_PARENTESIS) {
			expr = procExpr();
			write->addExpr(expr);
			while(m_current.type == TT_COMMA) {
				advance();
				expr = procExpr();
				write->addExpr(expr);
			}
	}
	eat(TT_CLOSE_PARENTHESIS);
	return write;
}

// <read>     ::= readln'(' <id> { ',' <id> } ')'
ReadCommand* SyntaticAnalysis::procRead() {
	int line = m_lex.line();
	eat(TT_READ_LN);
	ReadCommand* read = new ReadCommand(line);
	eat(TT_OPEN_PARENTESIS);
	Variable* var = procId();
	read->addVariable(var);
	while(m_current.type == TT_COMMA) {
		advance();
		Variable* var = procId();
		read->addVariable(var);
	}
	eat(TT_CLOSE_PARENTHESIS);
	return read;
}

// <boolexpr> ::= [not] <cmpexpr> [(and| or) <boolexpr> ]
BoolExpr* SyntaticAnalysis::procBooleanexpr() {
	int line = m_lex.line();
	bool notop = false;
	if(m_current.type == TT_NOT){
		notop = true;
		advance();
	}
	BoolExpr* left = procCmpexpr();
	if(m_current.type == TT_AND || m_current.type == TT_OR) {
		CompositeBoolExpr::Op op;
		if(m_current.type == TT_AND) {
			eat(TT_AND);
			op = CompositeBoolExpr::AND;
		} else {
			eat(TT_OR);
			op = CompositeBoolExpr::OR;
		}
		BoolExpr* right = procBooleanexpr();
		left = new CompositeBoolExpr(line, left, op, right);
	}
	if(notop){
		left = new NotBollExpr(line, left);
	}
	return left;
}

// <cmpexpr>  ::= <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr>
BoolExpr* SyntaticAnalysis::procCmpexpr() {
	int line = m_lex.line();
	Expr* left = procExpr();
	SingleBoolExpr::Op op;
	if(m_current.type == TT_EQUAL) {
		eat(TT_EQUAL);
		op = SingleBoolExpr::EQUAL;
	} else if(m_current.type == TT_NOT_EQUAL) {
		eat(TT_NOT_EQUAL);
		op = SingleBoolExpr::NOT_EQUAL;
	} else if(m_current.type == TT_LOWER) {
		eat(TT_LOWER);
		op = SingleBoolExpr::LOWER;
	} else if(m_current.type == TT_GREATER) {
		eat(TT_GREATER);
		op = SingleBoolExpr::GREATER;
	} else if(m_current.type == TT_LOWER_EQUAL) {
		eat(TT_LOWER_EQUAL);
		op = SingleBoolExpr::LOWER_EQUAL;
	} else if(m_current.type == TT_GREATER_EQUAL) {
		eat(TT_GREATER_EQUAL);
		op = SingleBoolExpr::GREATER_EQUAL;
	} else {
		showError();
	}
	Expr* right = procExpr();
	BoolExpr* boolExpr = new SingleBoolExpr(line, left, op, right);
	return boolExpr;
}

// <expr>     ::= <term> { ('+' | '-') <term> }
Expr* SyntaticAnalysis::procExpr() {
	int line = m_lex.line();
	BinaryExpr::Op op;

	Expr* left = procTerm();
	Expr* right;

	while(m_current.type == TT_ADD || m_current.type == TT_SUB) {
		if(m_current.type == TT_ADD) {
			eat(TT_ADD);
			op = BinaryExpr::ADD;
		} else {
			eat(TT_SUB);
			op = BinaryExpr::SUB;
		}
		right = procTerm();

		left = new BinaryExpr(line, left, op, right);
	}
	return left;
}

// <term>     ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntaticAnalysis::procTerm() {
	int line = m_lex.line();
	BinaryExpr::Op op;

	Expr* left = procFactor();
	Expr* right;

	while(m_current.type == TT_MUL || m_current.type == TT_DIV || m_current.type == TT_MOD) {
		if(m_current.type == TT_MUL) {
			eat(TT_MUL);
			op = BinaryExpr::MUL;
		} else if(m_current.type == TT_DIV) {
			eat(TT_DIV);
			op = BinaryExpr::DIV;
		} else {
			eat(TT_MOD);
			op = BinaryExpr::MOD;
		}
		right = procFactor();

		left = new BinaryExpr(line, left, op, right);
	}
	return left;
}

// <factor>   ::= <value> | <id> | '(' <expr> ')'
Expr* SyntaticAnalysis::procFactor() {
	int line = m_lex.line();
	Expr* expr;
	if (m_current.type == TT_NUMBER || m_current.type == TT_FLOAT || m_current.type == TT_STRING) {
		Type* t = procValue();
		expr = new ConstExpr(line, t);

	} else if(m_current.type == TT_VAR) {
		expr = procId();

	} else {
		eat(TT_OPEN_PARENTESIS);
		expr = procExpr();
		eat(TT_CLOSE_PARENTHESIS);
	}
	return expr;
}

// <value>    ::= <integer> | <real> | <string>
Type* SyntaticAnalysis::procValue() {
	Type* value;
	if(m_current.type == TT_NUMBER) {
		value= procInteger();

	} else if(m_current.type == TT_FLOAT) {
		value= procReal();

	} else {
		value= procStrign();
	}
	return value;
}

// <var>       ::= id
Variable* SyntaticAnalysis::procId() {
	std::string tmp = m_current.token;
	int line = m_lex.line();

	eat(TT_VAR);

	Variable* var = new Variable(line, tmp);
	return var;
}

// <integer>   ::= number
IntegerValue* SyntaticAnalysis::procInteger() {
	std::string tmp = m_current.token;

	eat(TT_NUMBER);

	int value = atoi(tmp.c_str());
	IntegerValue* intval = new IntegerValue(value);
	return intval;
}

// <real>      ::= float
RealValue* SyntaticAnalysis::procReal() {
	std::string tmp = m_current.token;

	eat(TT_FLOAT);

	double value = std::stod(tmp.c_str());
	RealValue* realval = new RealValue(value);
	return realval;
}

// <string>    ::= string
StringValue* SyntaticAnalysis::procStrign() {
	std::string tmp = m_current.token;

	eat(TT_STRING);

	StringValue* strval = new StringValue(tmp);
	return strval;
}

#include<iostream>
#include <string>

#include"WriteCommand.h"

// <write>    ::= (write| writeln) '(' [ <expr> { ',' <expr> } ] ')'

WriteCommand::WriteCommand(int line, bool writeln)
    : Command(line), m_writeln(writeln) {
}

WriteCommand::~WriteCommand(){
	for (std::list<Expr*>::iterator it = m_expr.begin(),
	     ed = m_expr.end(); it != ed; it++) {
		Expr* expr = *it;
		delete expr;
	}
}

void WriteCommand::addExpr(Expr* expr) {
	m_expr.push_back(expr);
}

void WriteCommand::execute(){
	Type* t;

	for (std::list<Expr*>::iterator it = m_expr.begin(),
	     ed = m_expr.end(); it != ed; it++) {
		Expr* expr = *it;
		t = expr->expr();
		if(t->type() == Type::IntegerType){
			IntegerValue* iv = (IntegerValue*) t;
			int value = iv->value();
			std::cout << value;
		} else if(t->type() == Type::RealType) {
			RealValue* rv = (RealValue*) t;
			double value = rv->value();
			std::cout << value;
		} else {
			StringValue* sv = (StringValue*) t;
			std::string value = sv->value();
			std::cout << value;
		}
	}
	if(!m_writeln){
		std::cout << "\n";
	}
}

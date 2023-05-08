#include "ForCommand.h"

ForCommand::ForCommand(int line, Variable* var, Expr* src, Expr* dst, Command* cmd)
	:Command(line), m_var(var), m_src(src), m_dst(dst), m_cmd(cmd) {
}

ForCommand::~ForCommand(){
	delete m_cmd;
	delete m_dst;
	delete m_src;
	delete m_var;
}

void ForCommand::execute(){
	Type* t1 = m_src->expr();
	Type* t2 = m_dst->expr();

	if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
		IntegerValue* iv1 = (IntegerValue*) t1;
		IntegerValue* iv2 = (IntegerValue*) t2;
		int value1 = iv1->value();
		int value2 = iv2->value();
		while(value1 < value2){
			m_cmd->execute();
			value1++;
		}
	} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
		RealValue* rv1 = (RealValue*) t1;
		RealValue* rv2 = (RealValue*) t2;
		double value1 = rv1->value();
		double value2 = rv2->value();
		while(value1 < value2){
			m_cmd->execute();
			value1 = value1 + 1.0;
		}
	}
}

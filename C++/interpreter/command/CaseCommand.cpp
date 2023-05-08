#include "CaseCommand.h"


CaseCommand::CaseCommand(int line, Expr* expr)
	:Command(line), m_expr(expr){
		m_expr->expr();
}

CaseCommand::~CaseCommand(){
	delete m_expr;
	for (std::list<CaseOption*>::iterator it = m_options.begin(),
	     ed = m_options.end(); it != ed; it++) {
		CaseOption* option = *it;
		delete option;
	}
	if(m_otherwise)
	delete m_otherwise;
}

void CaseCommand::addOption(Type* value, Command* cmd){
	CaseOption* option = new CaseOption(value, cmd);
	m_options.push_back(option);
}

void CaseCommand::setOtherwise(Command* cmd){
	m_otherwise = cmd;
}

// <case>     ::= case<expr> of{ <value> ':'<body> ';' } [ else<body> ';' ] end
void CaseCommand::execute(){
	bool elsecmd = true;
	Type* tvalue = m_expr->expr();
	int casevalue = -1;

	if(tvalue->type() == Type::IntegerType){
		IntegerValue* iv = (IntegerValue*) tvalue;
		casevalue = iv->value();
	}

	for (std::list<CaseOption*>::iterator it = m_options.begin(),
	     ed = m_options.end(); it != ed; it++) {
		CaseOption* option = *it;
		Type* t = option->m_value;
		int value = 0;

		if(t->type() == Type::IntegerType){
			IntegerValue* iv = (IntegerValue*) t;
			value = iv->value();
		}
		if(casevalue == value){
			elsecmd = false;
			option->m_cmd->execute();
		}
	}
	if(elsecmd && m_otherwise){
		m_otherwise->execute();
	}
}

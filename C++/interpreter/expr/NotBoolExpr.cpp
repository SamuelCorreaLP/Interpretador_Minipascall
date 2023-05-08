#include "NotBoolExpr.h"

NotBollExpr::NotBollExpr(int line, BoolExpr* expr)
	: BoolExpr(line), m_expr(expr){

}

NotBollExpr::~NotBollExpr(){
	delete m_expr;
}

bool NotBollExpr::expr(){
	return !m_expr->expr();
}

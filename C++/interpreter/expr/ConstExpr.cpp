#include"ConstExpr.h"

ConstExpr::ConstExpr(int line, Type* value)
    : Expr(line),m_value(value){
}

ConstExpr::~ConstExpr() {
	delete m_value;
}

Type* ConstExpr::expr() {
	return m_value;
}

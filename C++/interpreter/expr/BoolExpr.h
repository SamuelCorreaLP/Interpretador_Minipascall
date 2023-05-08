#ifndef BOOL_EXPR_H
#define BOOL_EXPR_H

#include "../value/Value.h"
#include "Expr.h"

class BoolExpr {
	public:
		BoolExpr(int line) : m_line(line) {}
		virtual ~BoolExpr() {}

		int getLine() const {return m_line;}
		virtual bool expr() = 0;

	private:
		int m_line;
};

#endif

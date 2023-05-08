#ifndef NOT_BOOL_EXPR_H
#define NOT_BOOL_EXPR_H

#include "BoolExpr.h"

class NotBollExpr : public BoolExpr {
	public:
		NotBollExpr(int line, BoolExpr* expr);
		virtual ~NotBollExpr();

		bool expr();

	private:
		BoolExpr* m_expr;
};

#endif

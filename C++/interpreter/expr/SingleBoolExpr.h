#ifndef SINGLE_BOOL_EXPR_H
#define SINGLE_BOOL_EXPR_H

#include "BoolExpr.h"
#include "../value/Type.h"
#include "../value/Value.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include"../value/StringValue.h"

class SingleBoolExpr : public BoolExpr {
	public:
		enum Op {
			EQUAL = 1,
			NOT_EQUAL = 2,
			LOWER = 3,
			LOWER_EQUAL = 4,
			GREATER = 5,
			GREATER_EQUAL = 6
		};

		SingleBoolExpr(int line, Expr* left, enum Op RelOp, Expr* right);
		virtual ~SingleBoolExpr();

		bool expr();

	private:
		Expr* m_left;
		enum Op m_BoolOp;
		Expr* m_right;
};

#endif

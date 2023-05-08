#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

#include "Expr.h"
#include "../value/Type.h"
#include "../value/Value.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"

class BinaryExpr : public Expr {
	public:
		enum Op {
			ADD = 1,
			SUB = 2,
			MUL = 3,
			DIV = 4,
			MOD = 5
		};
		BinaryExpr(int line, Expr* left, enum Op op, Expr* right);
		virtual ~BinaryExpr();

		virtual Type* expr();

	private:
		Expr* m_left;
		enum Op m_op;
		Expr* m_right;
};

#endif

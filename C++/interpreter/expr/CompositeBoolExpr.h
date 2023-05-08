#ifndef COMPOSITE_BOOL_EXPR_H
#define COMPOSITE_BOOL_EXPR_H

#include "BoolExpr.h"

class CompositeBoolExpr : public BoolExpr {
	public:
		enum Op{
			AND = 1,
			OR = 2
		};
		CompositeBoolExpr(int line,BoolExpr* left, enum Op RelOp, BoolExpr* right);
		virtual ~CompositeBoolExpr();

		int getLine();
		bool expr();

	private:
		BoolExpr* m_left;
		enum Op m_BoolOp;
		BoolExpr* m_right;
};

#endif

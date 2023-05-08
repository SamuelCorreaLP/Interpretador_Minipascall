#include "CompositeBoolExpr.h"

CompositeBoolExpr::CompositeBoolExpr(int line,BoolExpr* left, enum Op RelOp, BoolExpr* right)
	:BoolExpr(line), m_left(left), m_BoolOp(RelOp), m_right(right) {

}

CompositeBoolExpr::~CompositeBoolExpr(){
	delete m_left;
	delete m_right;
}

bool CompositeBoolExpr::expr(){
	bool left = m_left->expr();
	bool right = m_right->expr();

	switch (m_BoolOp){
	case CompositeBoolExpr::AND:
		return left && right;
		break;
	case CompositeBoolExpr::OR:
		return left || right;
		break;
	}
	return 0;
}

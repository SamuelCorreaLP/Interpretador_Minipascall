#include "AssignCmd.h"

AssignCmd::AssignCmd(int line, Variable* left, Expr* right)
	:Command(line), m_left(left), m_right(right){

}
AssignCmd::~AssignCmd(){
	delete m_left;
	delete m_right;
}
void AssignCmd::execute(){
	Type* value = m_right->expr();
	m_left->setValue(value);
}

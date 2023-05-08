#include "BinaryExpr.h"
#include <iostream>

BinaryExpr::BinaryExpr(int line, Expr* left, enum BinaryExpr::Op op, Expr* right)
	: Expr(line), m_left(left), m_op(op), m_right(right) {
}

BinaryExpr::~BinaryExpr() {
	delete m_left;
	delete m_right;
}

Type* BinaryExpr::expr() {
	Type* none;
	Type* t1 = m_left->expr();
	Type* t2 = m_right->expr();

	switch (m_op) {
		case BinaryExpr::ADD:
			if(t1->type() == Type::IntegerType || t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();
				int resul = value1 + value2;
				IntegerValue* intresul = new IntegerValue(resul);

				return intresul;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();
				double resul = value1 + value2;
				RealValue* realresul = new RealValue(resul);

				return realresul;
			} else {
				std::cout << "Operação invalida soma" << std::endl;
				exit(1);
			}
			break;
		case BinaryExpr::SUB:
			if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();
				int resul = value1 - value2;
				IntegerValue* intresul = new IntegerValue(resul);

				return intresul;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();
				double resul = value1 - value2;
				RealValue* realresul = new RealValue(resul);

				return realresul;
			} else {
				std::cout << "Operação invalida subtração" << std::endl;
				exit(1);
			}
			break;
		case BinaryExpr::MUL:
			if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();
				int resul = value1 * value2;
				IntegerValue* intresul = new IntegerValue(resul);

				return intresul;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();
				double resul = value1 * value2;
				RealValue* realresul = new RealValue(resul);

				return realresul;
			} else {
				std::cout << "Operação invalida multiplicação" << std::endl;
				exit(1);
			}
			break;
		case BinaryExpr::DIV:
			if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();
				int resul = value1 / value2;
				IntegerValue* intresul = new IntegerValue(resul);

				return intresul;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();
				double resul = value1 / value2;
				RealValue* realresul = new RealValue(resul);

				return realresul;
			} else {
				std::cout << "Operação invalida divisão" << std::endl;
				exit(1);
			}
			break;
		case BinaryExpr::MOD:
				if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();
				int resul = value1 % value2;
				IntegerValue* intresul = new IntegerValue(resul);

				return intresul;
			} else {
				std::cout << "Operação invalida modulo" << std::endl;
				exit(1);
			}
			break;
	}
	return none;
}

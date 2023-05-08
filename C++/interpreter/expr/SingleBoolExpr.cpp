#include "SingleBoolExpr.h"
#include <iostream>

SingleBoolExpr::SingleBoolExpr(int line, Expr* left, enum Op RelOp, Expr* right)
	: BoolExpr(line), m_left(left), m_BoolOp(RelOp), m_right(right) {
}

SingleBoolExpr::~SingleBoolExpr(){
	delete m_left;
	delete m_right;
}

bool SingleBoolExpr::expr(){
	Type* none;
	Type* t1 = m_left->expr();
	Type* t2 = m_right->expr();

	switch(m_BoolOp){
		case SingleBoolExpr::EQUAL:
			if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();

				return value1 == value2;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();

				return value1 == value2;

			} else if(t1->type() == Type::StringType && t2->type() == Type::StringType){
				StringValue* sv1 = (StringValue*) t1;
				StringValue* sv2 = (StringValue*) t2;
				std::string value1 = sv1->value();
				std::string value2 = sv2->value();

				return value1 == value2;
			} else {
				std::cout << "Operação invalida " << std::endl;
				exit(1);
			}
			break;
		case SingleBoolExpr::NOT_EQUAL:
			if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();

				return value1 != value2;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();

				return value1 != value2;

			} else if(t1->type() == Type::StringType && t2->type() == Type::StringType){
				StringValue* sv1 = (StringValue*) t1;
				StringValue* sv2 = (StringValue*) t2;
				std::string value1 = sv1->value();
				std::string value2 = sv2->value();

				return value1 != value2;
			} else {
				std::cout << "Operação invalida" << std::endl;
				exit(1);
			}
			break;
		case SingleBoolExpr::LOWER:
			if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();

				return value1 < value2;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();

				return value1 < value2;

			} else {
				std::cout << "Operação invalida" << std::endl;
				exit(1);
			}
			break;
		case SingleBoolExpr::LOWER_EQUAL:
		if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();

				return value1 <= value2;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();

				return value1 <= value2;

			} else {
				std::cout << "Operação invalida" << std::endl;
				exit(1);
			}
			break;
		case SingleBoolExpr::GREATER:
			if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();

				return value1 > value2;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();

				return value1 > value2;

			} else {
				std::cout << "Operação invalida" << std::endl;
				exit(1);
			}
			break;
		case SingleBoolExpr::GREATER_EQUAL:
			if(t1->type() == Type::IntegerType && t2->type() == Type::IntegerType){
				IntegerValue* iv1 = (IntegerValue*) t1;
				IntegerValue* iv2 = (IntegerValue*) t2;
				int value1 = iv1->value();
				int value2 = iv2->value();

				return value1 >= value2;

			} else if(t1->type() == Type::RealType && t2->type() == Type::RealType) {
				RealValue* rv1 = (RealValue*) t1;
				RealValue* rv2 = (RealValue*) t2;
				double value1 = rv1->value();
				double value2 = rv2->value();

				return value1 >= value2;

			} else {
				std::cout << "Operação invalida" << std::endl;
				exit(1);
			}
			break;
	}
	return none;
}

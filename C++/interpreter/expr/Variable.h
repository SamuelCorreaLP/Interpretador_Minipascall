#ifndef VARIABLE_H
#define VARIABLE_H

#include <map>
#include <string>

#include "Expr.h"
#include "../value/Value.h"

class Variable : public Expr {
	public:
		Variable(int line, const std::string& name);
		virtual ~Variable();

		const std::string& getName() const {return m_name;}
		void setValue(Type* value);
		virtual Type* expr();

	private:
	const std::string m_name;
};

#endif

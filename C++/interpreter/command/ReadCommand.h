#ifndef READ_COMMAND_H
#define READ_COMMAND_H

#include <list>
#include "Command.h"
#include "../expr/Variable.h"
#include "../value/Type.h"
#include "../value/Value.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include "../value/StringValue.h"

class Variable;

class ReadCommand : public Command {
	public:
		ReadCommand(int line);
		virtual ~ReadCommand();

		virtual void addVariable(Variable* var);
		virtual void execute();

	private:
		std::list<Variable*> m_vars;
};

#endif

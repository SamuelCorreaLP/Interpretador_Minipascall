#ifndef FOR_COMMAND_H
#define FOR_COMMAND_H

#include "Command.h"
#include "../expr/Variable.h"
#include "../expr/Expr.h"
#include "../value/Type.h"
#include "../value/Value.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include "../value/StringValue.h"

class ForCommand : public Command {
	public:
		ForCommand(int line, Variable* var, Expr* src, Expr* dst, Command* cmd);
		virtual ~ForCommand();

		virtual void execute();

	private:
		Variable* m_var;
		Expr* m_src;
		Expr* m_dst;
		Command* m_cmd;
};

#endif

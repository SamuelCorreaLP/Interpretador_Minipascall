#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include <list>
#include "Command.h"
#include "../expr/Expr.h"
#include "../value/Type.h"
#include "../value/Value.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include "../value/StringValue.h"


class WriteCommand : public Command {
	public:
		WriteCommand(int line, bool writeln);
		virtual ~WriteCommand();

		virtual void addExpr(Expr* expr);
		virtual void execute();

	private:
		std::list<Expr*> m_expr;
		bool m_writeln;
};

#endif

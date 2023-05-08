#ifndef CASE_COMMAND_H
#define CASE_COMMAND_H

#include <list>
#include "Command.h"
#include "CaseOption.h"
#include "../expr/Expr.h"
#include "../value/Value.h"
#include "../value/IntegerValue.h"

class CaseCommand : public Command {
	public:
		CaseCommand(int line, Expr* expr);
		virtual ~CaseCommand();

		void addOption(Type* value, Command* cmd);
		void setOtherwise(Command* cmd);
		virtual void execute();

	private:
		Expr* m_expr;
		Command* m_otherwise;
		std::list<CaseOption*> m_options;
};

#endif

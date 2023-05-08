#ifndef ASSIGN_COMMAND_H
#define ASSIGN_COMMAND_H

#include "Command.h"
#include"../expr/Expr.h"
#include "../expr/Variable.h"

class AssignCmd : public Command {
	public:
		AssignCmd(int line, Variable* left, Expr* right);
		virtual ~AssignCmd();

		virtual void execute();

	private:
		Variable* m_left;
		Expr* m_right;
};

#endif

#ifndef CASE_OPTION_H
#define CASE_OPTION_H

#include "Command.h"
#include "../value/Value.h"

class CaseOption{
	public:
		CaseOption(Type* value, Command* cmd) : m_value(value), m_cmd(cmd) {}
		~CaseOption() {delete m_value; delete m_cmd;}

		Type* m_value;
		Command* m_cmd;
};

#endif

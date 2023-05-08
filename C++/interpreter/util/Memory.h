#ifndef MEMORY_H
#define MEMORY_H

#include <map>
#include <set>
#include <string>
#include "../value/Value.h"

class Memory {
	public:

	static void registryVariable(std::string name, Type* value);
	static void registryConstant(std::string name, Type* value);

	static Type* read(std::string name);
	static void write(std::string mane, Type* value);

	private:
	static std::map<std::string, Type*> m_memory;
	static std::set<std::string> m_consts;
};

#endif

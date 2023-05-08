#include "Memory.h"
#include <iostream>

std::map<std::string, Type*> Memory::m_memory;
std::set<std::string> Memory::m_consts;

void Memory::registryVariable(std::string name, Type* value){
	Memory::m_memory[name] = value;
}

void Memory::registryConstant(std::string name, Type* value){
	if(Memory::m_consts.insert(name).second == false) {
		std::cout << "Operação invalida - constante com nome repetido" << std::endl;
		exit(1);
	} else {
		Memory::m_consts.insert(name);
		Memory::m_memory[name] = value;
	}
}

Type* Memory::read(std::string name){
	return Memory::m_memory[name];
}

void Memory::write(std::string name, Type* value){
	Memory::m_memory[name] = value;
}

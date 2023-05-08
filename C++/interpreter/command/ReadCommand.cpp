#include<iostream>
#include <string>

#include "ReadCommand.h"

ReadCommand::ReadCommand(int line)
	: Command(line) {

}
ReadCommand::~ReadCommand(){
for (std::list<Variable*>::iterator it = m_vars.begin(),
	     ed = m_vars.end(); it != ed; it++) {
		Variable* var = *it;
		delete var;
	}
}

void ReadCommand::addVariable(Variable* var){
	m_vars.push_back(var);
}
void ReadCommand::execute(){
	char c;
	for (std::list<Variable*>::iterator it = m_vars.begin(),
	     ed = m_vars.end(); it != ed; it++) {
		Variable* var = *it;
		std::string input;
		std::cin >> input;

		bool hasletter = false;
		bool hasdot = false;
		for(long unsigned int i=0; i < input.length(); ++i){
			c = input.at(i);
			if(c == '.'){
				hasdot = true;
			} else if(isalpha(c)) {
				hasletter = true;
			}
		}
		if(hasletter){
			Type* t = new StringValue(input);
			var->setValue(t);
		} else if(hasdot){
			double value = std::stod(input.c_str());
			Type* t = new RealValue(value);
			var->setValue(t);
		} else {
			int value = atoi(input.c_str());
			Type* t = new IntegerValue(value);
			var->setValue(t);
		}
	}
}

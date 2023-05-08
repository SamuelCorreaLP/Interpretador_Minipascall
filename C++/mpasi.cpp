#include <cstdio>
#include <iostream>
#include <cstdlib>

#include "lexical/LexicalAnalysis.h"
#include "lexical/Lexeme.h"
#include "syntatic/SyntaticAnalysis.h"
#include "interpreter/command/Command.h"

// Interpretador de mini pascal
// Trabalho TP1 de Linguagem de Programação
// Professor: Andrei Rimsa Álvares
// Aluno: Samuel Correa Lucas Pereira
// 27-02-2021

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " [Pascal program]" << std::endl;
		exit(1);
	}

	try{
		Lexeme lex;
		LexicalAnalysis l(argv[1]);
		SyntaticAnalysis s(l);

		Command* cmd = s.start();
		cmd->execute();

		delete cmd;

		//testa parte Lexica
		// while ((lex = l.nextToken()).type > 0) {
		// 	std::cout << lex.str() << std::endl;
		// }
		// std::cout << lex.str() << std::endl;

	} catch (const std::string& error) {
		std::cerr << "error: " << error << std::endl;
	}

	return(0);
}

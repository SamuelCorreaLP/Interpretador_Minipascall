#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"

#include "../interpreter/expr/Expr.h"
#include "../interpreter/expr/Variable.h"
#include "../interpreter/expr/ConstExpr.h"
#include "../interpreter/expr/BinaryExpr.h"

#include "../interpreter/expr/BoolExpr.h"
#include "../interpreter/expr/SingleBoolExpr.h"
#include "../interpreter/expr/NotBoolExpr.h"
#include "../interpreter/expr/CompositeBoolExpr.h"

#include "../interpreter/command/Command.h"
#include "../interpreter/command/ForCommand.h"
#include "../interpreter/command/WhileCommand.h"
#include "../interpreter/command/AssignCmd.h"
#include "../interpreter/command/BlocksCommand.h"
#include "../interpreter/command/ReadCommand.h"
#include "../interpreter/command/WriteCommand.h"
#include "../interpreter/command/CaseCommand.h"
#include "../interpreter/command/RepeatCommand.h"
#include "../interpreter/command/IfCommand.h"

#include "../interpreter/value/Value.h"
#include "../interpreter/value/IntegerValue.h"
#include "../interpreter/value/RealValue.h"
#include "../interpreter/value/StringValue.h"


class SyntaticAnalysis {
	public:
		SyntaticAnalysis(LexicalAnalysis& lex);
		virtual ~SyntaticAnalysis();

		Command* start();

	private:
		LexicalAnalysis& m_lex;
		Lexeme m_current;

		void advance();
		void eat(enum TokenType type);
		void showError();

		Command* procProgram();

		void procConst();
		void procVar();

		Command* procBody();
		BlocksCommand* procBlock();
		Command* procCmd();

		AssignCmd* procAssing();
		IfCommand* procIf();
		CaseCommand* procCase();
		WhileCommand* procWhile();
		RepeatCommand* procRepeat();
		ForCommand* procFor();
		WriteCommand* procWrite();
		ReadCommand* procRead();

		BoolExpr* procBooleanexpr();
		BoolExpr* procCmpexpr();

		Expr* procExpr();
		Expr* procTerm();
		Expr* procFactor();

		Variable* procId();
		Type* procValue();
		IntegerValue* procInteger();
		RealValue* procReal();
		StringValue* procStrign();
};

#endif

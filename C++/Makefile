CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mpasi
OBJS=mpasi.o \
	lexical/SymbolTable.o \
	lexical/LexicalAnalysis.o \
	syntatic/SyntaticAnalysis.o \
	interpreter/command/BlocksCommand.o \
	interpreter/command/AssignCmd.o \
	interpreter/command/CaseCommand.o \
	interpreter/command/ForCommand.o \
	interpreter/command/IfCommand.o \
	interpreter/command/RepeatCommand.o \
	interpreter/command/WhileCommand.o \
	interpreter/command/ReadCommand.o \
	interpreter/command/WriteCommand.o \
	interpreter/util/Memory.o \
	interpreter/expr/ConstExpr.o \
	interpreter/expr/Variable.o \
	interpreter/expr/BinaryExpr.o \
	interpreter/expr/SingleBoolExpr.o \
	interpreter/expr/NotBoolExpr.o \
	interpreter/expr/CompositeBoolExpr.o \
	interpreter/value/IntegerValue.o \
	interpreter/value/RealValue.o \
	interpreter/value/StringValue.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	cp $(TARGET) /usr/local/bin

mpasi.o: lexical/LexicalAnalysis.h syntatic/SyntaticAnalysis.h interpreter/command/Command.h
lexical/SymbolTable.o: lexical/TokenType.h
lexical/LexicalAnalysis.o: lexical/LexicalAnalysis.h  lexical/Lexeme.h  lexical/SymbolTable.h
syntatic/SyntaticAnalysis.o: syntatic/SyntaticAnalysis.h interpreter/util/Memory.h
interpreter/command/BlocksCommand.o: interpreter/command/BlocksCommand.h
interpreter/command/AssignCmd.o: interpreter/command/AssignCmd.h
interpreter/command/CaseCommand.o: interpreter/command/CaseCommand.h
interpreter/command/ForCommand.o: interpreter/command/ForCommand.h
interpreter/command/IfCommand.o: interpreter/command/IfCommand.h
interpreter/command/RepeatCommand.o: interpreter/command/RepeatCommand.h
interpreter/command/WhileCommand.o: interpreter/command/WhileCommand.h
interpreter/command/ReadCommand.o: interpreter/command/ReadCommand.h
interpreter/command/WriteCommand.o: interpreter/command/WriteCommand.h
interpreter/util/Memory.o: interpreter/util/Memory.h
interpreter/expr/ConstExpr.o: interpreter/expr/ConstExpr.h
interpreter/expr/Variable.o: interpreter/expr/Variable.h interpreter/util/Memory.h
interpreter/expr/BinaryExpr.o: interpreter/expr/BinaryExpr.h
interpreter/expr/SingleBoolExpr.o: interpreter/expr/SingleBoolExpr.h
interpreter/expr/NotBoolExpr.o: interpreter/expr/NotBoolExpr.h
interpreter/expr/CompositeBoolExpr.o: interpreter/expr/CompositeBoolExpr.h
interpreter/value/IntegerValue.o: interpreter/value/IntegerValue.h
interpreter/value/RealValue.o: interpreter/value/RealValue.h
interpreter/value/StringValue.o: interpreter/value/StringValue.h

$(TARGET): $(OBJS)
		   $(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

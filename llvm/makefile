.PHONY: clean distclean default

LLVMCONFIG=llvm-config

CXX=c++
CXXFLAGS=-Wall -g `$(LLVMCONFIG) --cxxflags`
LDFLAGS=`$(LLVMCONFIG) --ldflags --system-libs --libs all`
PYTHON=python

default: GinNTony

test:
	$(PYTHON) run_tests.py

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

lexer.o: lexer.cpp lexer.hpp parser.hpp general.hpp error.hpp

parser.hpp parser.cpp: parser.y
	bison -dv -o parser.cpp parser.y

parser.o: parser.cpp lexer.hpp ast.hpp symbol.hpp general.hpp error.hpp ast.cpp codegen.hpp

GinNTony: lexer.o parser.o 
	$(CXX) $(CXXFLAGS) -o GinNTony lexer.o parser.o error.cpp general.cpp symbol.cpp codegen.cpp  $(LDFLAGS)

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o *.imm *.asm *.ll *.out *.s

distclean: clean
	$(RM) GinNTony
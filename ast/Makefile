.PHONY: clean distclean default

CXX=c++

default: GinNTony

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

lexer.o: lexer.cpp lexer.hpp parser.hpp ast.hpp

parser.hpp parser.cpp: parser.y
	bison -dv -o parser.cpp parser.y

parser.o: parser.cpp lexer.hpp ast.hpp

GinNTony: lexer.o parser.o
	$(CXX) $(CXXFLAGS) -o GinNTony lexer.o parser.o

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o GinNTony

distclean: clean
	$(RM) GinNTony
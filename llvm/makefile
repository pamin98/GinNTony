# .PHONY: clean distclean default

# LLVMCONFIG=llvm-config

# CXX=c++
# # CXXFLAGS=-g -Wall
# CXXFLAGS=-Wall -g `$(LLVMCONFIG) --cxxflags`
# LDFLAGS=`$(LLVMCONFIG) --ldflags --system-libs --libs all`

# default: GinNTony

# lexer.cpp: lexer.l
# 	flex -s -o lexer.cpp lexer.l

# lexer.o: lexer.cpp lexer.hpp parser.hpp ast.hpp general.hpp error.hpp

# parser.hpp parser.cpp: parser.y
# 	bison -dv -o parser.cpp parser.y

# parser.o: parser.cpp lexer.hpp ast.hpp symbol.hpp general.hpp error.hpp

# ast: ast.hpp ast.cpp $(LDFLAGS)

# GinNTony: lexer.o parser.o 
# 	$(CXX) $(CXXFLAGS) -o GinNTony lexer.o parser.o error.cpp general.cpp symbol.cpp $(LDFLAGS)

# clean:
# 	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o 

# distclean: clean
# 	$(RM) GinNTony


#----------------------------------------------------------------------------------------

.PHONY: clean distclean default

LLVMCONFIG=llvm-config

CXX=c++
CXXFLAGS=-Wall -g `$(LLVMCONFIG) --cxxflags`
LDFLAGS=`$(LLVMCONFIG) --ldflags --system-libs --libs all`

default: GinNTony

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

lexer.o: lexer.cpp lexer.hpp parser.hpp general.hpp error.hpp

parser.hpp parser.cpp: parser.y
	bison -dv -o parser.cpp parser.y

parser.o: parser.cpp lexer.hpp ast.hpp symbol.hpp general.hpp error.hpp ast.cpp codegen.hpp

GinNTony: lexer.o parser.o 
	$(CXX) $(CXXFLAGS) -o GinNTony lexer.o parser.o error.cpp general.cpp symbol.cpp codegen.cpp  $(LDFLAGS)

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o 

distclean: clean
	$(RM) GinNTony
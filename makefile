#OS Type: Linux/Win DJGPP
ifdef OS
	EXE=.EXE
else
	EXE=
endif

CFLAGS=-g
CC=gcc

GinNTony$(EXE): lexer.o
		$(CC) $(CFLAGS) -o $@ $^ -lfl

lexer.c: Lexer.l
		flex -s -o $@ $<

.PHONY: clean distclean

clean:
		$(RM) lexer.c *.o *~

distclean: clean
		$(RM) GinNTony$(EXE)
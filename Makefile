CC = g++
LEX = lex -ll
YACC = yacc -d -t -y

all: compiler
.PHONY: git-commit

git-commit: 
	git checkout master
	git add Makefile
	git add *.y *.l
	git commit -a -m "Commit from Makefile"
	git push

y.tab.o: parser.y
	$(YACC) -o y.tab.c parser.y
	$(CC) -c y.tab.c

lex.yy.o: parser.l
	$(LEX) parser.l
	$(CC) -c lex.yy.c

compiler: y.tab.o lex.yy.o parser.hh parser.cc interpreter.hh interpreter.cc
	$(CC) -o compiler y.tab.o lex.yy.o parser.hh parser.cc interpreter.hh interpreter.cc

clean:
	rm *.o compiler y.tab.c y.tab.h lex.yy.c
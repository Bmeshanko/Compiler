CC = g++ -g -std=c++17
LEX = lex -ll
YACC = yacc -y -d -t --debug

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

compiler: y.tab.o lex.yy.o parser.h parser.c interpreter.hh interpreter.cc
	$(CC) -o compiler lex.yy.o y.tab.o parser.h parser.c interpreter.hh interpreter.cc

clean:
	rm *.o compiler y.tab.c y.tab.h lex.yy.c
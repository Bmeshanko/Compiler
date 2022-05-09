CC=g++ -g -std=c++17
LEX=lex -ll
YACC=yacc -y -d -t --debug

all: git-commit compiler

.PHONY: git-commit
git-commit:
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.cc *.l *.h *.hh *.o *.y
	git commit -a -m "Commit from Makefile" >> .local.git.out || echo
	git push >> .local.git.out || echo

lex.yy.o: compiler.l
	$(LEX) -o lex.yy.cc compiler.l
	$(CC) -c lex.yy.cc

y.tab.o: compiler.y
	$(YACC) -o y.tab.cc compiler.y
	$(CC) -c y.tab.cc

compiler.o: compiler.cc compiler.hh
	$(CC) -c compiler.cc

numparser.o: numparser.cc numparser.hh
	$(CC) -c numparser.cc

compiler: compiler.o y.tab.o lex.yy.o numparser.o
	$(CC) -o compiler compiler.o lex.yy.o y.tab.o numparser.o

clean:
	rm *.o compiler



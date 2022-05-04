CC=g++ -g -std=c++17
LEX=lex -ll
YACC=yacc -y -d -t --debug

all: compiler git-commit

.PHONY: git-commit
git-commit:
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.cc *.l *.h *.hh *.o
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

compiler: compiler.o lex.yy.o y.tab.o
	$(CC) -o compiler compiler.o lex.yy.o y.tab.o

clean:
	rm *.o compiler



CC=g++ -g -std=c++17
LEX=lex -ll
YACC=yacc -y -d -t --debug

all: compiler git-commit

.PHONY: git-commit
git-commit:
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.cc *.l *.h *.hh
	git commit -a -m "Commit from Makefile" >> .local.git.out || echo
	git push >> .local.git.out || echo

compiler: compiler.l
	$(LEX) -o lex.yy.cc compiler.l
	$(YACC) -o y.tab.cc compiler.y
	$(CC) lex.yy.cc y.tab.cc -o compiler

clean:
	rm lex.yy.c *.o compiler



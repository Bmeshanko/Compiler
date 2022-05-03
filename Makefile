CC=g++ -g -std=c++17
LEX=lex -ll

all: git-commit compiler

.PHONY: git-commit
git-commit:
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.cc *.l *.h
	git commit -a -m "Commit from Makefile" >> .local.git.out || echo
	git push >> .local.git.out || echo

compiler: compiler.l lex.yy.cc
	$(LEX) -o lex.yy.cc compiler.l
	$(CC) lex.yy.cc -o compiler

clean:
	rm lex.yy.c *.o compiler



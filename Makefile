CC=g++ -g -std=c++17
LEX=lex -l

all: git-commit compiler

.PHONY: git-commit
git-commit:
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.cc *.l *.h
	git commit -a -m "Commit from Makefile" >> .local.git.out || echo
	git push >> .local.git.out || echo

lex.yy.o: compiler.l
	$(LEX) -o lex.yy.c compiler.l
	$(CC) lex.yy.cc -c

compiler: lex.yy.o
	$(CC) lex.yy.o -o compiler

clean:
	rm lex.yy.c *.o compiler



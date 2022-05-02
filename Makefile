CC=g++ -g -std=c++17
LEX=lex -l

all: git-commit compiler

.PHONY: git-commit
git-commit:
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.c *.l *.h
	git commit -a -m "Commit from Makefile" >> .local.git.out || echo
	git push >> .local.git.out || echo

lex.yy.o: compiler.l
	$(LEX) -o lex.yy.cc compiler.l
	$(CC) -c lex.yy.cc

compiler: lex.yy.o
	$(CC) -o compiler lex.yy.o

clean:
	rm lex.yy.c *.o compiler



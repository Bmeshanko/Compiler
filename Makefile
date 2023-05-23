CC = g++ -g -std=c++17
LEX = lex -ll
YACC = yacc -y -d -t --debug

all: compiler
.PHONY: git-commit

git-commit: 
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.y *.l
	git commit -a -m "Commit from Makefile" >> .local.git.out || echo
	git push >> .local.git.out || echo

interpreter.o: interpreter.y
	$(YACC) -o interpreter.c interpreter.y
	$(CC) -c interpreter.c

parser.o: parser.y
	$(YACC) -o parser.c parser.y
	$(CC) -c parser.c

lex.yy.o: parser.l
	$(LEX) parser.l
	$(CC) -c lex.yy.c

compiler: parser.o lex.yy.o tree.hh
	$(CC) -o compiler lex.yy.o parser.o tree.hh

interpreter: interpreter.o lex.yy.o tree.hh
	$(CC) -o compiler lex.yy.o interpreter.o tree.hh

clean:
	rm *.o compiler
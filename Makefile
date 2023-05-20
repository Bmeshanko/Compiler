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

y.tab.o: parser.y
	$(YACC) parser.y
	$(CC) -c y.tab.c

lex.yy.o: parser.l
	$(LEX) parser.l
	$(CC) -c lex.yy.c

compiler: y.tab.o lex.yy.o
	$(CC) -o compiler lex.yy.o y.tab.o

clean:
	rm *.o compiler
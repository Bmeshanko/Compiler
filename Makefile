CC = g++ -g -std=c++17
LEX = lex -ll
YACC = yacc -y -d -t --debug

all: git-commit compiler
.PHONY: git-commit

git-commit: 
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.y *.l
	git commit -a -m "Commit from Makefile" >> .local.git.out || echo
	git push >> .local.git.out || echo

lex.yy.o: parser.l
	$(LEX) parser.l
	$(CC) -c lex.yy.cc

y.tab.o: parser.y
	$(YACC) parser.y
	$(CC) -c y.tab.cc

compiler: lex.yy.o y.tab.o
	$(CC) -o compiler lex.yy.o y.tab.o

clean:
	rm *.o compiler
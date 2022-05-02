all: git-commit compiler

.PHONY: git-commit
git-commit:
	git checkout master >> .local.git.out || echo
	git add Makefile
	git add *.c *.l *.h
	git commit -a -m "Commit from Makefile" >> .local.git.out || echo
	git push >> .local.git.out || echo

compiler:
	rm lex.yy.c compiler
	lex compiler.l
	gcc lex.yy.c -ll -o compiler

clean:
	rm lex.yy.c *.o compiler



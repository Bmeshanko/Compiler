#include <stdio.h>
#include <stdlib.h>

int _pnum(int num) {
	printf("%d\n", num);
}

int (*pnum)(const char*, ...) = _pnum;

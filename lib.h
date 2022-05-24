#include <stdio.h>
#include <stdlib.h>

int _pnum(int num) {
	printf("%d\n", num);
	return 0;
}

int (*pnum)(const char*, ...) = _pnum;

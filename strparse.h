#include <stdlib.h>
#include <string.h>

char * substr(char * str, int start) {
	if (start < 0 || start > strlen(str)) return NULL;

	char * sub = (char *) malloc(strlen(str) - start);

	for (int i = start; i < strlen(str); i++) {
		*(sub + i - start) = *(str + i);
	}

	return sub;
}

char * substr(char * str, int start, int end) {
	if (start > end || end > strlen(str) || start < 0) return NULL;

	char * sub = (char *) malloc(end - start);

	for (int i = start; i < end; i++) {
		*(sub + i - start) = *(str + i);
	}

	return sub;
}

char charAt(char * str, int index) {
	return *(str + index);
}

// Returns the index of the first instance
// Of character ch in string str.
int indexOf(char * str, char ch) {
	for (int i = 0; i < strlen(str); i++) {
		if (*(str + i) == ch) {
			return i;
		}
	}

	return -1;
}

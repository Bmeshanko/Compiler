#include <stdlib.h>
#include <string.h>

const char * substr(char * str, int start) {
	char * sub = (char *) malloc(strlen(str) - start);
	for (int i = start; i < strlen(str); i++) {
		*(sub + i - start) = *(str + i);
	}
	return sub;
}

const char * substr(char * str, int start, int end) {

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

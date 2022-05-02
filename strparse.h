#include <stdlib.h>
#include <string.h>

const char * substr(char * str, int start) {
	char * sub = malloc(strlen(str) - start);
	for (int i = start; i < strlen(str); i++) {
		*(sub + i - start) = *(str + i);
	}
	return sub;
}

const char * substr(char * str, int start, int end) {

}

char charAt(char * str, int index) {

}

int indexOf(char * str, char ch) {

}

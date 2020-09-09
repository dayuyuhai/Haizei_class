#include <stdio.h>

#define EO_A(a, b) EO(a, b, ==)
#define EO(a, b, comp) { \
	if (a comp b) printf("OK"); \
}

int main() {
	EO_A(2, 2);
	return 0;
}


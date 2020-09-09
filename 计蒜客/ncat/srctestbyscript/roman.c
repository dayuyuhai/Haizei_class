#include "roman.h"

static const char *symbol[] = { "I", "V", "X", "L", "C", "D", "M",
                                "-V", "-X", "-L", "-C", "-D", "-M",
                                "=V", "=X", "=L", "=C", "=D", "=M" };

static char* addsymbol(char* dst, int index)
{
	for (int i = 0; *(symbol[index] + i) != '\0'; i++) {
		*(dst++) = *(symbol[index] + i);
	}
	return dst;
}

static char* _roman(char* dst, int src, int index)
{
	if (src != 0) {
		dst = _roman(dst, src / 10, index + 1);
		src %= 10;
		if (src >= 9) {
			dst = addsymbol(dst, index * 2);
			dst = addsymbol(dst, index * 2 + 2);
			src -= 9;
		}
		if (src >= 5) {
			dst = addsymbol(dst, index * 2 + 1);
			src -= 5;
		}
		if (src >= 4) {
			dst = addsymbol(dst, index * 2);
			dst = addsymbol(dst, index * 2 + 1);
			src -= 4;
		}
		while (src > 0) {
			dst = addsymbol(dst, index * 2);
			src--;
		}
	}
	return dst;
}

char* to_roman_numeral(char* dst, int src)
{
	*(_roman(dst, src, 0)) = '\0';
	return dst;
}


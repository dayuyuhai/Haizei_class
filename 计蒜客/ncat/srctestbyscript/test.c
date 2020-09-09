/*************************************************************************
	> File Name: test.c
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 20 Jun 2020 08:19:14 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
	char str[100];
	char *s;
	int i = 1;
	switch (argc) {
		case 2:
			while (scanf("%s", str)) {
				if (!strcmp(argv[1], "-d")) printf("%d\t%s\n", i, str);
				else printf("%s\t%s\n", to_roman_numeral(s, i), str);
				i++;
			} break;
		case 3:
			fp1 = fopen(argv[2], "r");
			while (fscanf(fp1, "%s", str) != EOF) {
				if (!strcmp(argv[1], "-d")) printf("%d\t%s\n", i, str);
				else printf("%s\t%s\n", to_roman_numeral(s, i), str);
				i++;
			} break;
		case 4:
			fp1 = fopen(argv[2], "r");
			fp2 = fopen(argv[3], "w");
			while (fscanf(fp1, "%s", str) ) {
				if (!strcmp(argv[1], "-d")) fprintf(fp2, "%d\t%s\n", i, str);
				else fprintf(fp2, "%s\t%s\n", to_roman_numeral(s, i), str);
				i++;
			} break;
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

/*************************************************************************
	> File Name: test.c
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 20 Jun 2020 08:19:14 PM CST
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include"roman.h"

int main(int argc, char *argv[]) {
    FILE *fp1 = stdin, *fp2 = stdout;
	char str[1000];
	int i = 1;
	if (argc >= 3) fp1 = fopen(argv[2], "r");
	if (argc == 4) fp2 = fopen(argv[3], "w");
	while (fscanf(fp1, "%[^\n]", str) != EOF) {
		fgetc(fp1);
		if (!strcmp(argv[1], "-d")) fprintf(fp2, "%d\t%s\n", i++, str);
		else {
			char s[25];
			to_roman_numeral(s, i++);
			fprintf(fp2, "%s\t%s\n", s, str);
		}
		str[0] = 0;
	}
	return 0;
}

#include <stdio.h>
#include "run.h"
#include <string.h>
#include <stdlib.h>

int main()
{
	const char *name_program = "./program";
	const char *name_in = "./in.txt";
	const char *name_out = "./out.txt";
	const char *name_right = "./right.txt";
	run(name_program, name_in, name_out);
	FILE *fpright = fopen(name_right, "r");
	FILE *fpout = fopen(name_out, "r");

	// Input your code here.
	char str[100];
	int flag = 1;
	while (1) {
		strcpy(str, fgets(fpright));
		if (str == EOF) break;
		if (strcmp(str, fgets(fpout))) {
			flag = 0;
			break;
		}
	}
	/*
	char str1[100];
	char str2[100];
	int flag = 1;
	int fla;
	int cnt = 0;
	while (1) {
		fla = 1;
		if (fscanf(fpright, "%[^\n]", str1) != EOF) {
			fgetc(fpright);
			cnt++;
			fla = 0;
		}
		if (fscanf(fpout, "%[^\n]", str2) != EOF) {
			fgetc(fpout);
			cnt--;
			fla = 0;
		}
		if (fla) break;
		if (strcmp(str1, str2)) {
			flag = 0;
			break;
		}
	}
	if (abs(cnt) > 1) flag = 0;
	*/
	printf("%s\n", flag ? "Accept" : "Wrong Answer");

	fclose(fpout);
	fclose(fpright);
	return 0;
}

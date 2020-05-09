/*************************************************************************
	> File Name: printf.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月09日 星期六 14时41分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdarg.h>

int my_printf(const char *frm, ...) {
	int cnt = 0;
	#define PUTC(a) putchar(a), ++cnt
	va_list arg;
	va_start(arg, frm);
	//不用i < strlen(frm) 它从当前字符串往后遍历，遍历到\0有一个cnt计算，时间不够好
	for (int i = 0; frm[i]; i++) {
		switch (frm[i]) {
			case '%' : {
				switch (frm[++i]) {
					case '%' : PUTC(frm[i]); break;
					case 'd' : {
						int x = va_arg(arg, int), temp = 0;
						int digit = 0;
						do {
							temp = temp * 10 + x % 10;
							x /= 10;
							digit++;
						} while (x);
						while (digit--) {
							PUTC(temp % 10 + '0');
							temp /= 10;
						}
					} break;
				}
			} break;

			default: PUTC(frm[i]); break;
		}
	}
	va_end(arg);
	#undef PUTC
	return cnt;
}
	
int main() {
	printf("hello world\n");
	my_printf("hello world\n");
	printf("%%\n");
	my_printf("%%\n");
	printf("int (123) = %d\n", 123);
	my_printf("int (123) = %d\n", 123);
	printf("int (1000) = %d\n", 1000);
	my_printf("int (1000) = %d\n", 1000);
	printf("int (0) = %d\n", 0);
	my_printf("int (0) = %d\n", 0);


	return 0;
}

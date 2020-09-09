实现一个我们起名为<code>ncat</code>的命令，其作用是把输入的内容每行前加上行号输出。

要求：

它可能有2～4个命令行参数，第一个命令行参数是它本身的名字，在这节里我们可以忽略，第二个参数一定是<code>-d</code>（表示 decimal）或者<code>-r</code>（表示 roman）中的一个，若为<code>-d</code>则行号用阿拉伯数字表示，若为<code>-r</code>则行号用罗马数字表示，若存在第三个参数则其表示输入文件的路径，若不存在则表示输入来自标准输入，若存在第四个参数则其表示输出文件的路径，若不存在则表示输出到标准输出。注意：行号与输入文本的回显之间用<code>\t</code>隔开



```shell
#MAKEFILE

CC = gcc

CFLAGS = -std=c99 -Wall -Werror

MAINOBJS = ncat.o roman.o

.PHONY: clean
ncat:  $(MAINOBJS) roman.h
	$(CC) $(CFLAGS) -o ncat $(MAINOBJS)

roman.o: roman.c roman.h
	$(CC) $(CFLAGS) -c -o roman.o roman.c

ncat.o: ncat.c roman.h
	$(CC) $(CFLAGS) -c -o ncat.o ncat.c

clean:
	$(RM) -- *.o ncat
```





```c
//nact.c

#include<stdio.h>
#include"roman.h"

int main(int argc, char *argv[]) {
!!! FILE *fp1 = stdin, *fp2 = stdout;
	char str[100];
	int i = 1;
    int flag =0;
!!! (argv[1][1] == 'd') && ++flag;  
	if (argc >= 3) fp1 = fopen(argv[2], "r");
	if (argc == 4) fp2 = fopen(argv[3], "w");
	while (fscanf(fp1, "%[^\n]", str) != EOF) {
!!!		fgetc(fp1);
		if (flag)) fprintf(fp2, "%d\t%s\n", i++, str);
		else {
			char s[5];
			to_roman_numeral(s, i++);
			fprintf(fp2, "%s\t%s\n", s, str);
		}
!!!		str[0] = 0;
	}
	return 0;
}
```



> line 7 : 开始自己写的条件分支，无文件参数用的scanf和printf，代码冗余
>
> line 11 : 避免在循环中使用strcmp，时间上浪费
>
> line 15 : 吞掉字符流中的\n，防止死循环
>
> line 22 : 清空字符串，保证下一次打印能正确找到'\0'
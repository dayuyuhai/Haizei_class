# 基于参考gtest功能的测试框架

## 一. gtest浅识

###  介绍

gtest是一个跨平台的(Liunx、Mac OS X、Windows、Cygwin、Windows CE and Symbian)C++单元测试框架，由google公司发布。gtest是为在不同平台上为编写C++测试而生成的。

###  简单使用

makefile作用：帮我们更好地进行编译和链接工程文件。

但是google中不会直接存在makefile文件，因为makefile文件的可移植性特别差，随着编译程序的环境不同而不同。

从而,有了cmake 根据你当前的环境生成makefile

```bash
cmake CMakeLists.txt
```



当需要别人的功能模块进行开发项目时，需要 头文件和对象文件的打包成的链接库，链接库在googletest/lib，头文件在googletest/googletest/include，我们将这两部分打包到自己的项目文件夹下，做好后，编写测试文件main.cpp

```c
#include<stdio.h>
#include<gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(func, add) {
	EXPECT_EQ(add(2, 3), 5);
	EXPECT_EQ(add(3, 4), 7);
	EXPECT_EQ(add(3, 6), 8);
	EXPECT_EQ(add(0, 3), 3);
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

```



为了能像gtest一样直接make做好编译等工作，创建makefile文件

```shell
.PHONY : clean # 防止当前文件夹下还有被命名为clean的文件
all:
	# 添加静态链接库到编译过程中
	g++ -std=c++11 -L ./lib/ main.cpp -lgtest
clean:
	rm -rf *.o a.out

```

make一下

```bash
make
```

测试结果

[一个暂时不存在的截图]



###  makefile相关思考

> 温馨提示：看完框架实现再来这里



测试：每次make之前都执行一次make clean的原因

一个makefile文件：

![image-20200619092729991](/home/waygu-beef/.config/Typora/typora-user-images/image-20200619092729991.png)



连续两次make一下

![image-20200619092852996](/home/waygu-beef/.config/Typora/typora-user-images/image-20200619092852996.png)



可见第二次make并没有执行haizei/born.o:以及main.o:后面的语句，可推出，makefile文件的工作机制是先从all中找是否存在main.o haizei/born.o文件，找到直接执行all下语句，找不到才会往下找。

如果每次make之前未进行make clean操作，执行的是上一次生成的对象文件，不是最新生成的。



上面是几天前的错误思考，现在，我们稍稍更改一下gtest.h文件

![image-20200624180514441](/home/waygu-beef/.config/Typora/typora-user-images/image-20200624180514441.png)



发现执行了两条语句，观察makefile第二部分被执行，第三部分没有，而它们的区别是，一个后面加了haizei/gtest.h，一个没有。可推测，每次执行make语句，不管第一行后面的文件存在与否，都会下去查，如果后面跟随的文件做了更改，便重新执行，没有则不重新执行



我们做的更改，是将EXPECT_NQ宏改成了==，重新编译的语句如上图，观察运行结果变化（仅部分截图）

![image-20200624181248329](/home/waygu-beef/.config/Typora/typora-user-images/image-20200624181248329.png)



我们的更改并没有起作用，原因是main函数与gtest.h相关，如上所说，但它并没有被重新编译。下面我们更改一下makefile文件，在main.o后面，也加上与其相关的头文件

![image-20200624180341591](/home/waygu-beef/.config/Typora/typora-user-images/image-20200624180341591.png)



不执行make clean，make一下（第二行编译语句上次已经执行，gtest .h对它来说未更改

![image-20200624181602416](/home/waygu-beef/.config/Typora/typora-user-images/image-20200624181602416.png)



​                                                                             执行结果

<img src="/home/waygu-beef/.config/Typora/typora-user-images/image-20200624181714121.png" alt="image-20200624181714121"  />



我们看到，即使没有用make clean，我们的程序也正确随着更改执行了。也就是说，如果写了一个完整完美的makefile，便不必每次更改都执行make clean，它会自动根据程序员的改动文件做相应的重新编译的链接。make clean的作用只是最终把没用的东西清一下



其实还没有完美，发现了么，如果更改main.c函数，还是不会重新编译main.c文件。我们在main.c文件中主函数内增加两条打印信息，并最后一次修改makefile

![image-20200624183443828](/home/waygu-beef/.config/Typora/typora-user-images/image-20200624183443828.png)



​                                                                                 执行结果

![image-20200624183527735](/home/waygu-beef/.config/Typora/typora-user-images/image-20200624183527735.png)



##  二. 根据gtest的测试数据所展示的表面形式，写自己的c语言测试框架

###  最终效果

观察即将用来测试的main.cpp文件

```c
#include<stdio.h>
#include<haizei/gtest.h>

int add(int a, int b) {
	return a + b;
}

TEST(testFunc, add) {
	EXPECT_EQ(add(3, 5), 8);
	EXPECT_NE(add(3, 5), 9);
	EXPECT_LT(add(6, 7), 13);
	EXPECT_GT(add(5, 5), 6);
	EXPECT_LE(add(4, 3), 7);
	EXPECT_GT(add(1, 2), 3);
}

TEST(testFunc, add2) {
	EXPECT_EQ(add(2, 1), 3.5);
	EXPECT_EQ(add(12, 1), 13);
}

TEST(test, Funcadd) {
	EXPECT_EQ(add(2, 13), 15);
	EXPECT_EQ(add(6, 18), 24);
}

int main() {
	return RUN_ALL_TESTS();
}

```



不难看出，我们应该实现的，无非就是TEST、 EXPECT、 RUN_ALL_TEST，先来看看最终需要呈现的样子，据此来实现自己的测试框架

<img src="/home/waygu-beef/.config/Typora/typora-user-images/image-20200619110831226.png" alt="image-20200619110831226" style="zoom: 33%;" />



###  思考过程

- TEST、RUN_ALL_TEST、EXPECT是啥

  TEST：没有返回值，用脚趾盖想也不是函数，那能是啥

  RUN_ALL_TEST：函数可以像它这么用，且程序最终都是return 0，所以它应该是有返回值的

  EXPECT：一想就是宏
  
  ```c
  // gtest.h
  
  #define TEST(a, b) void a##b()
  
  #define EXPECT_EQ(a, b) printf(#a " = " #b " %s", \
  	(a) == (b) ? "TRUE" : "FALSE");
  
  int RUN_ALL_TEST();
  ```
  
  ```c
  // test.cc
  
  int RUN_ALL_TEST() {
  	return 0;
  }
  ```
  
  ```shell
  # makefile
  
  .PHONY: clean
  
  all: main.o test.o 
  	g++ main.o test.o
  test.o: haizei/test.cc haizei/gtest.h
  	g++ -c -I./ haizei/test.cc
  main.o: main.cpp
  	g++ -c -I./ main.cpp
  clean:
  	rm -rf *.o a.out
  
  ```
  
  
  
  这里RUN_ALL_TEST没起什么作用，接下来要改进的是，当调用RUN_ALL_TEST时才执行每个测试用例
  
  ```c
  // gtest.h
  
  #define TEST(a, b) \
  void a##_##b(); \
  __attribute__((constructor)) \
  void add##_##a##_##b() { \
  	addfunc(a##_##b, #a "_" #b); \
  } \
  void a##_##b() \
  
  #define EXPECT_EQ(a, b) printf(#a " = " #b " %s\n", \
  	(a) == (b) ? "TRUE" : "FALSE");
  
  typedef void (*funcp)();
  
  int RUN_ALL_TESTS();
  void addfunc(funcp, const char *);
  
  ```
  
  ```c
  // test.cc
  
  #include<stdio.h>
  #include<haizei/gtest.h>
  
  int func_cnt = 0;
  
  struct fun {
  	funcp func;
  	const char *name;
  } func_arr[100];
  
  int RUN_ALL_TESTS() {
  	for (int i = 0; i < func_cnt; i++) {
  		if (i > 0) printf("\n");
  		printf("[----RUN----] %s\n", func_arr[i].name);
  		func_arr[i].func();
  		printf("[--RUN END--]\n");
  	}
  	return 0;
  }
  
  void addfunc(funcp func, const char *name) {
  	func_arr[func_cnt].func = func;
  	func_arr[func_cnt].name = name;
  	func_cnt++;
  }
  
  ```
  
  ```shell
  # makefile
  工程规范:将可执行文件放在/bin目录下
  .PHONY: clean
  
  all: main.o haizei/test.o 
  	g++ main.o haizei/test.o -o ./bin/haizei
  haizei/test.o: haizei/test.cc haizei/gtest.h
  	g++ -c -I./ -o haizei/test.o haizei/test.cc
  main.o: main.cpp
  	g++ -c -I./ main.cpp
  clean:
  	rm -rf ./bin/haizei main.o haizei/test.o
  ```
  
  
  
  ​                                                                          执行效果
  
  ![image-20200624203515825](/home/waygu-beef/.config/Typora/typora-user-images/image-20200624203515825.png)



####  promotion1

给EXPECT宏实现更多比较功能，优化输出

```c
#define EXPECT(a, b, comp) printf("[-----------] " \
	#a " " #comp " " #b " %s\n", \
	(a) comp (b) ? "TRUE" : "FALSE");

#define EXPECT_EQ(a, b) EXPECT(a, b, ==)
#define EXPECT_NE(a, b) EXPECT(a, b, !=)
#define EXPECT_LT(a, b) EXPECT(a, b, <)
#define EXPECT_GT(a, b) EXPECT(a, b, >)
#define EXPECT_LE(a, b) EXPECT(a, b, <=)
#define EXPECT_GE(a, b) EXPECT(a, b, >=)
```



​                                                                                 执行效果

<img src="/home/waygu-beef/.config/Typora/typora-user-images/image-20200624214626358.png" alt="image-20200624214626358" style="zoom:33%;" />



####  promotion2

设计输出统计信息

```c
// gtest.h

#define EXPECT(a, b, comp) {\
	__typeof(a) _a = (a); \
	__typeof(b) _b = (b); \
	cnt++; \
	if (_a comp _b) cnt_success++; \
	printf("[-----------] " #a " " #comp " " #b " %s\n", \
	_a comp _b ? "TRUE" : "FALSE"); \
}

extern int cnt, cnt_success;
```

```c
int cnt, cnt_success;

int RUN_ALL_TESTS() {
	for (int i = 0; i < func_cnt; i++) {
		cnt = cnt_success = 0;
		if (i > 0) printf("\n");
		printf("[----RUN----] %s\n", func_arr[i].name);
		func_arr[i].func();
		double rate = 100.0 * cnt_success / cnt;
		printf("[%8.2lf%%  ] total : %d  success : %d\n", rate, cnt, cnt_success);
		printf("\n");
	}
	return 0;
}
```



​                                                                                 执行结果

<img src="/home/waygu-beef/.config/Typora/typora-user-images/image-20200624222128131.png" alt="image-20200624222128131" style="zoom: 33%;" />



####  promotion3

加颜色

```c
格式 ：printf("\033[字背景颜色;字体颜色m 字符串 \033[0m" );
```

具体颜色网址：https://blog.csdn.net/wangweiqiang1325/article/details/51787534

格式都差不多，用宏封装一下，省着每次写一堆

```c
// gtest.h

#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define COLOR_HL(a, b) "\033[1;" #b "m" a "\033[0m"

#define GREEN(a) COLOR(a, 32)
#define RED(a) COLOR(a, 31)
#define YELLOW(a) COLOR(a, 33)
#define BLUE(a) COLOR(a, 34)

#define GREEN_HL(a) COLOR_HL(a, 32)
#define RED_HL(a) COLOR_HL(a, 31)
#define YELLOW_HL(a) COLOR_HL(a, 33)
#define BLUE_HL(a) COLOR_HL(a, 34)
```



​                                                                                   执行效果

<img src="/home/waygu-beef/.config/Typora/typora-user-images/image-20200625102745188.png" alt="image-20200625102745188" style="zoom:33%;" />





####  promotion4

设计输出错误提示信息

这里唯一难点是actual那一行，如何输出类型不确定的add函数返回值

使用_Generic关键字：

```c
#define TYPE_STR(a) _Generic((a), \
	int : "%d", \
	double : "%lf", \
	long long : "%lld", \
	float : "%f", \
	char * : "%s" \
)

```

这里还需要一个宏辅助

```c
#define P(a, color) { \
	char frm[1000]; \
	sprintf(frm, color("%s"), TYPE_STR(a)); \
	printf(frm, a); \
}
```

原因：

```c
printf(YELLOW_HL(TYPE_STR(_a)), _a); 
```

展开结果，报错

```c
printf("\033[1;" "33" "m" _Generic((_a), int : "%d", double : "%lf", long long : "%lld", float : "%f", char * : "%s" ) "\033[0m", _a);
```



```c
P(_a, YELLOW_HL);
```

展开结果，正确

```c
{   char frm[1000]; 
	sprintf(frm, "\033[1;" "33" "m" "%s" "\033[0m", _Generic((_a), int : "%d", double : "%lf", long long : "%lld", float : "%f", char * : "%s" )); 
    printf(frm, _a); };
```



```c
// gtest.h

	if (_a comp _b) cnt_success++; \
	else { \
		printf("\n"); \
		printf("\t" YELLOW_HL("%s:%d: Failure") "\n", __FILE__, __LINE__); \
		printf("\t\t" YELLOW_HL("expect : " #a " " #comp " " #b "\n")); \
		printf("\t\t" YELLOW_HL("actual : ")); \
		P(a, YELLOW_HL); \
		printf(YELLOW_HL(" vs " #b)); \
		printf("\n\n"); \
	} \
```



此时程序出现玄学报错，究其原因，是_Generic宏只适用于c语言，我们要更改makefile文件中的g++为gcc，并将文件名更改成.c

```shell
# makefile

.PHONY: clean

all: main.o haizei/test.o 
	gcc main.o haizei/test.o -o ./bin/haizei
haizei/test.o: haizei/test.c haizei/gtest.h
	gcc -c -I./ -o haizei/test.o haizei/test.c
main.o: main.c
	gcc -c -I./ main.c
clean:
	rm -rf ./bin/haizei main.o haizei/test.o

```



​                                                                              执行结果

<img src="/home/waygu-beef/.config/Typora/typora-user-images/image-20200625115748734.png" alt="image-20200625115748734" style="zoom:33%;" />





####  promotion5

我们已经实现了最终的输出效果，但是代码还有需要优化的地方。我们开辟了一个空间100的数组，而实际上，测试案例的数量是不应该被限制的，我们应对此做相应优化。



没有数量限制，想到了链表。我们将链表做成外骨骼，使它可以用在不同场景。



```c
// linklist.h

#ifndef _LINKLIST_H
#define _LINKLIST_H

#define offset(T, name) ((long long)(&(((T *)(0))->name)))
#define Head(p, T, name) ((T *)(((char *)p) - offset(T, name)))

struct LinkNode {
    struct LinkNode *next;
};

#endif
```



```c
// gtest.h

#include <haizei/linklist.h>

struct Function {
	funcp func;
	const char *name;
	struct LinkNode p;
};

```



```c
// test.cc

struct Function func_head, *func_tail = &func_head;

int RUN_ALL_TESTS() {
	for (struct LinkNode *p = func_head.p.next; p; p = p->next) {
		struct Function *func = Head(p, struct Function, p);
		printf(GREEN_HL("[====RUN====]") RED_HL(" %s") "\n", func->name);
		func->func();

void add_func(funcp func, const char *str) {
	struct Function *temp = (struct Function *)calloc(1, sizeof(struct Function));
	temp->func = func;
	temp->name = strdup(str);
	func_tail->p.next = &(temp->p);
	func_tail = temp;
	return ;
}
```


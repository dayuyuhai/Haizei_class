# Preface

## 0- 数学知识

###  1. 平方和通项公式推导

​		F(n) =  n^3^  - (n - 1)^3^ = 

​		F(n - 1) = 

​		……



###  2. 逆运算

- 加法是减法的逆运算，减法不是加法的逆运算

  a - b = c, a = b + c 但 b !=  a + c

- 乘法是除法的逆运算，（不为0时），除法不是乘法的逆运算


- 逆运算要满足交换率


- 异或是逆运算




### 3. 两个数的最小公倍数

​		两个数乘积除以它们最大公约数



#  First

##  0- 输入输出

### printf函数

```c
#include<stdio.h>
int printf(const char *format, ...);
//format   格式控制字符串
//...              可变参数列表
//返回值     输出字符的数量
```



### scanf函数

返回值：成功读入参数的个数

- scanf("%d", &n);    1个
- scanf("hello");        0个
- -1是不可以的，所以有了!=EOF

```c
#include<stdio.h>

int main() {
	char str[100] = {0};
	int ret;
	while ((ret = scanf("%[^\n]s", str)) != EOF) {
		getchar();    //吞掉一个字符，此处是吞掉\n
		printf(" has %d digit\n", printf("%s", str));
	}
	return 0;
}

//[^\n]正则表达式，意思是除了\n任何字符都当字符读入，不加这个，则hello world会当作两个字符串读入
//如果没有getchar()尝试运行程序printf("%s %d\n", str, ret)，会一直循环输出，观察ret的值。scanf读入的是字符流，下一次读入的时候指针仍停留在\n，所以一直未读进参数并向下进行
```



### printf家族

```c
#include<stdio.h>
#define swap(a, b) {\
	__typeof(a) __temp = a;\
	a = b; b = __temp;\
}
//typeof()也是一个宏，生成一个和a同类型的变量

int main() {
	int n;
	char str[100] = {0}, buffer[100] = {0};
	char *p = str, *q = buffer;
	scanf("%d", &n);  //stdin 0
	printf("%4d\n", n);  //stdout 1 stderr 2 EOF -1 //这些粉粉都东西都是一个文件
	sprintf(str, "%d.%d.%d.%d", 192, 168, 1, 10);
//做的是字符串的拼接操作
	printf("%s", str);
	if (n & 1) {
		sprintf(q, "(%s)", p);
		swap(p, q);
	}
	if (n & 2) {
		sprintf(q, "[%s]", p);
		swap(p, q);
	}
	if (n & 4) {
		sprintf(q, "{%s}", p);
		swap(p, q);
	}
	printf("%s\n", p);
	FILE *fout = fopen("output", "w");
    fprintf(output, "stdout = %s\n", p);  //output文件里
	fprintf(stdout, "stdout = %s\n", p);  //显示在终端上
	fprintf(stderr, "stderr = %s\n", p);     //显示在终端上  

	return 0;
}
```



> 对于32、33行代码： 
>
> ./a.out > output
>
> 标准输出重定向，标准输出进了文件里，标准错误输出还在终端上
>
> ./a.out 2> erroutput
>
> 标准错误输出重定向
>
> 这样就把标准输出和标准错误输出分离开来





##  1- ifelse慢 怎么办

- 顺序执行才能实现并行，有分支就不能提前装好下一条指令，就变成串行，效率低，少用if else，可以用&& || 代替

- 分支预测，预测对了开启并行模式，不对还能串行

  ```c
  #define likely(x) __builtin_expect(!!(x), 1);
  //!!(x)  归一化，为0 仍0 ，为其他归1
  //告诉cpu经常出现，加载if里的并行语句
  #define unlikely(x) __builtin_expect(!!(x), 0);
  //告诉cpu不经常出现，不加载if里的并行语句,加载else里的语句
  ```

  

- builtin家族 (搜)


![2020-05-03 15-47-09屏幕截图](/home/waygu-beef/图片/2020-05-03 15-47-09屏幕截图.png)





##  2- int32_t那些



```c
#include<stdio.h>
#include<inttypes.h>

int main() {
    int64_t a = 256;
    int b = 6;
    printf("sizeof(a) = %lu\n", sizeof(a));
    printf("sizeof(b) = %lu\n", sizeof(b));
    printf("INT8_MIN = %d\n", INT8_MIN);
    printf("INT8_MAX = %d\n", INT8_MAX);
    printf("PRId64 = %s\n", PRId64);
    printf("PRId32 = %s\n", PRId32);
    printf("PRId16 = %s\n", PRId16);
	printf("%"PRId64"\n", a);   
	//PRId64能根据系统自动替换成该系统下的格式站位符
	//PRId64/32/16会被解析成 lld, d, hd （linux）
	printf("hello" " world" "\n");   //异曲同工
	return 0;
}
```



##  3- 数学函数

| 常用函数           | 在math.h里                       |
| ------------------ | -------------------------------- |
| pow(a, b)          | fabs(n)                          |
| sqrt(n)            | log(n)                           |
| ceil(n)            | log10(n)   (其他用换底公式求)    |
| floor(n)           | acos(n)      #define PI acos(-1) |
| abs(n)  (stdlib.h) |                                  |



##  4- 随机数



```c
                                            统计偶数个数
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main() {
	int cnt = 0;
	for (int i = 1; i <= 10; i++) {
		int val = rand() % 100; //rand取的是int范围内所有数
		cnt += !(val & 1);  //学着点
	}
	printf("%d\n", cnt);
	return 0;
}

//最后编译多次还是那些随机数字，其实是伪随机，第一个数字随机，后面的数字是用我们看不见的方式生成，如第一个数字是7，下一个一定是49
//srand(time(0))  time(0)是程序的时间，以当前时间变量做为随机种子，随机生成数字，也是伪随机，只是当前变化规律不是我们简单分析能得到的
```



##  5- 位运算和优先级

- 位运算  ^ & | ~ >> <<

  ```c
  //举个栗子
  交换a, b
  a ^= b;
  b ^= a;
  a ^= b;
  //异或满足交换率
  //相同为0，不同为1
  //0异或谁还谁
  ```

  

- 基本优先级

  链接（假）：百度搜索优先级



#   Second

##  0- 函数的声明和定义

声明 ：有这东西

**定义 ：东西啥样**



##  1-一种编程技巧：递归

### 四步

1. 赋予语义信息
2. 边界条件处理
3. 处理过程和递归过程
4. 结果返回：return或传出参数



### 递归特点

1. 自己调用自己

2. 范围缩小



### 数学归纳法：异曲同工

已知k(0)成立，若k(i)成立，k(i + 1)也成立，不必纠结过程



### 🌰

```c
#include<stdio.h>

int fac(int n) {
	if (n < 2) return 1;
	return n * fac(n - 1);
}

int main() {
	int n;
	while(~scanf("%d", &n)) {
		printf("%d\n", fac(n));
	}
	return 0;
}

```



##  2- 二分查找

### 🌰

```c
                               三角形数
#include<iostream>
using namespace std;

int Triangle(int n) {
	return n * (n + 1) / 2;
}

int binary_search(int x) {
	int head = 1, tail = x, mid;
	while (head <= tail) {
		mid = (head + tail) >> 1;
		if (Triangle(mid) == x) return mid;
		if (Triangle(mid) > x) tail = mid - 1;
		else head = mid + 1;
	}
	return 0;
}

int main() {
	int n;
	while (~scanf("%d", &n)) {
		printf("%d\n", binary_search(n));
	}
	return 0;
}

```



##  3- 函数指针

### **作用**

**帮我们定义一个分段函数**

### 🌰

```c
int g(int (*f1)(int), int (*f2)(int), int (*f3)(int), int x) {
	if (x < 0) {
		return f1(x);
	}
	if (x < 100) {
		return f2(x);
	}
	return f3(x);
}
```



**一个小应用 顺带二分查找**

```c
                             欧拉45题
#include<iostream>
#include<inttypes.h>
using namespace std;

int64_t Triangle(int64_t n) {
	return n * (n + 1) / 2;
}

int64_t Pentagonal(int64_t n) {
	return n * (3 * n - 1) / 2;
}

int64_t Hexagonal(int64_t n) {
	return n * (2 * n - 1);
}

int binary_search(int64_t (*func)(int64_t n), int64_t x) {
	int head = 1, tail = x, mid;
	while (head <= tail) {
		mid = (head + tail) >> 1;
		if (func(mid) == x) return mid;
		if (func(mid) > x) tail = mid - 1;
		else head = mid + 1;
	}
	return 0;
}

int main() {
	int n = 144;
	for (;; n++) {
		if (binary_search(Triangle, Hexagonal(n)) == 0) continue;
		if (binary_search(Pentagonal, Hexagonal(n)) == 0) continue;
		printf("%"PRId64"\n", Hexagonal(n));
		break;
	}
	return 0;
}

```



##  4- 辗转相除

### **能求**

1. 求最大公约数（辗转相除）

2. 求ax + by = d的一族整数解（扩展欧几里得）d是a，b最大公约数

### **推导过程**

自己想

### 🌰

```c
#include<iostream>
using namespace std;

int gcd(int a, int b) {
	return (b ? gcd(b, a % b) : a);
}

int main() {
	int a, b;
	while(~scanf("%d%d", &a, &b)) {
		printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
	}
	return 0;
}
```

```c
#include<iostream>
using namespace std;

int ex_gcd(int a, int b, int *x, int *y) {
	if (!b) {
		*x = 1;
	    *y = 0;
		return a;
	}
	int xx, yy, ret = ex_gcd(b, a % b, &xx, &yy);
	*x = yy;
	*y = xx - a / b * yy;
    
//上面改成
//	int ret = ex_gcd(b, a % b, y, x);
//	y -= a / b * (*x);

	return ret;
}

int main() {
	int a, b, x, y;
	while(~scanf("%d%d", &a, &b)) {
		printf("gcd(%d, %d) = %d\n", a, b, ex_gcd(a, b, &x, &y));
		printf("%d * %d + %d * %d = %d\n", a, x, b, y, a * x + b * y);
	}
	return 0;
}
```





#  Third

##  0- 变参函数

### 函数声明

```c
int max_int (int a, ...);
```

### 函数使用 : va一族

- va_list：变量类型，它定义的变量存三个点里的参数


- va_start：以a作为定义点，取列表的第一个参数


- va_arg：获取变参列表的下一个参数，不断往后 （若需记录值用中间变量存）


- va_end：结束整个变参列表的动作




### 🌰

```c
                      求n个变量的最大值
#include<stdio.h>
#include<inttypes.h>
#include<stdarg.h>

int max_int(int n, ...) {
	int ans = INT32_MIN, temp;
	va_list arg;
	va_start(arg, n);
	while (n--) {
		temp = va_arg(arg, int);    //这是一个宏，只不过表现得像一个函数
		if (temp > ans) ans = temp;
	}
	va_end(arg);
	return ans;
}

int main() {
	printf("%d\n", max_int(3, 1, 5, 3));
	printf("%d\n", max_int(2, 1, 6));
	printf("%d\n", max_int(3, 1, 6, 5, 27));
	return 0;
}
```



##  1- 实现printf函数（1.0）



```c
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
```



##  2- 实现printf函数（2.0）



```c
#include<stdio.h>
#include<stdarg.h>
#include<inttypes.h>
#define PUTC(a) putchar(a), ++cnt;
int reverse_num(int num, int *temp) {
	int digit = 0;
	do {
		*temp = *temp * 10 + num % 10;
		num /= 10;
		digit++;
	} while (num);
	return digit;
}

int output_num(int num, int digit) {
	int cnt = 0;
	while (digit--) {
		putchar(num % 10 + '0'), cnt++;
		num /= 10;
	}
	return cnt;
}

void output_int(int cnt, va_list arg) {
	int xx = va_arg(arg, int);
	uint32_t x;
	if (xx < 0) {
		x = -xx, PUTC('-');
	} else x = xx;
	int num1 = x / 100000, num2 = x % 100000;
	int temp1 = 0, temp2 = 0;
	int digit1 = reverse_num(num1, &temp1);
	int digit2 = reverse_num(num2, &temp2);
	if (num1) digit2 = 5;
	else digit1 = 0;
	cnt += output_num(temp1, digit1);
	cnt += output_num(temp2, digit2);

}

int my_printf(const char *frm, ...) {
	int cnt = 0;
	va_list arg;
	va_start(arg, frm);
	for (int i = 0; frm[i]; i++) {
		switch (frm[i]) {
			case '%' : {
				switch (frm[++i]) {
					case '%' : PUTC(frm[i]); break;
					case 'd' : {
						output_int(cnt, arg);
					} break;
					case 's': {
						const char *str = va_arg(arg, const char *);
						for (int i = 0; str[i]; i++) {
							PUTC(str[i]);
						}
					} break;
				}
			} break;

			default: PUTC(frm[i]); break;
		}
	}
	va_end(arg);
	return cnt;
}

#undef PUTC
	
int main() {
	int a = -123;
	char str[100] = "I love Haizei";
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
	printf("int (a) = %d\n", a);
	my_printf("int (a) = %d\n", a);
	printf("INT32_MAX = %d\n", INT32_MAX);
	my_printf("INT32_MAX = %d\n", INT32_MAX);
	printf("INT32_MIN = %d\n", INT32_MIN);
	my_printf("INT32_MIN = %d\n", INT32_MIN);
	printf("str = %s\n", str);
	my_printf("str = %s\n", str);
	return 0;
}

```



## 3- 实现随机点名小程序

```c
#include<iostream>
#include<time.h>
using namespace std;
#define max_n 16

char name[max_n][20] = {"杨宇晨", "严志伟", "何进康", "刘雨欣", "吴根胜",
	"周缘", "张晓宇", "张本超", "张芝涵", "张雨桐", "曹政", "樊帅朋",
	"艾艺", "郑佳伟", "魏嘉锐", "黄啸峰"};

int flag[max_n] = {0};
void output_name(int n) {
	srand(time(0));
	for (int i = 0; i < n;) {
		int index = rand() % max_n;
		if (flag[index]) continue;
		printf("%s ", name[index]);
		flag[index] = 1, i++;
	}
	printf("\n");
	return ;
}

int str_to_int(char *str) {
	int cnt = 0;
	for (int i = 0; str[i]; i++) {
		cnt = cnt * 10 + str[i] - '0';
	}
	return cnt;
}

int main(int argc, char *argv[]) {
	char str[3] = {0};
	if (argc < 2) {
		output_name(1);
	} else {
		sprintf(str, "%s", argv[1]);
		int n = str_to_int(str);
		if (n > max_n) {
			printf("最多%d个\n", max_n);
			exit(0);
		}
		output_name(n);
	}
	return 0;
}
```





# Forth

##  0- 数组

### 数组赋值

```c
for (int i = 0; i < 10; i++) {
	scanf("%d, arr + i");
}
```



### 关于数组地址

```c
void func(int *a) {
	printf("a[0] = %d, *a = %d\n", a[0], *a);
	//arr[0] 即 *(arr + 0)
    int *p
    printf("p = %p, p + 1 = %p\n", p, p + 1);  //也是移到下一块
    //为什么数组能直接传指针，与此行代码异曲同工
    return ;
}

int main() {
    int arr[10];
	printf("arr[0] = %p\n", &arr[0]);
	//%p打印地址
	//数组地址是arr[0]地址, arr + 1是移到下一块（一块的字节大小是存储数据类型的大小）

    func(arr);
    return 0;
}

```



### 高维数组传参 

- 重点：表现形式一致

```c
void func2(int **b)                      //不可，因为表现形式不同

void func2() {
    int **b;
    printf("b = %p, b + 1 = %p\n", b, b + 1);           //移动的大小是指针变量的大小
    return ;
}

void func2(int (*b)[9]) {                      //正确方式
    printf("b = %p, b + 1 = %p\n", b, b + 1);
    return ;
}

void func2(int (*b)[9][6]) {                      //三维正确方式
    printf("b = %p, b + 1 = %p\n", b, b + 1);
    return ;
}

int main() {
    int arr2[4][9];
    printf("arr2 = %p, arr2 + 1 = %p\n", arr2, arr2 + 1);   //差36个字节
    func2(arr2);
    return 0;
}
```





#  Fifth

##  0- 函数和数组

- **函数是压缩的数组，数组是压缩的函数**。

  它们有类似的映射性质



##  1- 牛顿迭代法

### 作用

- 求解高元方程的根

>  只能要收敛的，不能是发散或来回震荡的（课后查）
>
> 雷神，o(1) （查）



### 基本代码

```c
#include<iostream>
#include<math.h>
using namespace std;
#define EPSL 1e-6

inline double F(double x, double n) {
	return x * x - n;
}

inline double f(double x) {
	return 2 * x;
}

double NewTon(double (*F)(double, double), double (*f)(double), double n) {
	double x1 = n / 2.0;
	while (fabs(F(x1, n)) > EPSL) {
		x1 -= F(x1, n) / f(x1);
	}
	return x1;
}

double my_sqrt(double n) {
	return NewTon(F, f, n);
}
	
int main() {
	double n;
	while (~scanf("%lf", &n)) {
		printf("%g\n", my_sqrt(n));
	}

	return 0;
}

```



##  2- 二分查找

- 处理的是单调的

- 时间复杂度是logn，1亿个数，顺序查找需要1亿次，二分需要31次

- ```c
  (head  > tail) //不存在
  (a[mid == x)   //查找到
  (a[mid] > x)    tail = mid - 1   (增)
  (a[mid] < x)    head = mid + 1
  ```



###   特殊情况

- 前面一堆1，后面一堆0，或反过来
- 找最后一个1或第一个1出现的位置
- 01抽象：1满足某个性质，0不满足

```c
#include<iostream>
#include<algorithm>
using namespace std;

int binary_search1(int *arr, int n) {
	int head = -1, tail = n - 1, mid;       //虚拟头
	while (head < tail) {
		mid = (head + tail + 1) >> 1;
		if (arr[mid] == 0) tail =  mid - 1;
		else head = mid;
	}
	return head;
}

int binary_search2(int *arr, int n) {
	int head = 0, tail = n, mid;
	while (head < tail) {
		mid = (head + tail) >> 1;
		if (arr[mid] == 0) head = mid + 1;
		else tail = mid;
	}
	return (head == n ? -1 : head);
}

int main() {
	int num[10] = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1};
	int a[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int b[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	cout << binary_search2(num, 10) << endl;
	return 0;
}

```



##  3- 爆栈

- 程序先加到内存，再加到缓存中


- 函数里开辟的空间都在栈区


- 内存有栈区和堆区，栈去是函数里定义的，堆区在函数外定义的（如函数外定义的数组）


- 栈区有 8MB 约等于 800万个字节   数组开1000万就炸了，整形开200万就炸了


- 每次递归函数自己调用自己，相当于来回重新将函数压入系统栈（函数所需空间），又复制了一份函数加入空间（开的变量啥的），找到递归出口才弹栈


- 所以 像求阶乘那样的尾递归容易爆栈



# Sixth

##  0- 宏和预处理

### 写在前面

- 以#开头的都是一类预处理命令



### 宏定义

1. 定义符号常量

   ```c
   #define PI 3.1415926
   ```

2. 定义傻瓜表达式

   ```c
   #define MAX(a, b) (a) > (b) ? (a) : (b)
   ```

3. 定义代码段

   ```c
   #define P(a) { \
   	printf("%d\n", a);     \
   }
   
   // \是连接符号，将本行代码与下一行连接表现为一行
   ```

   

> 宏的相比于函数功能更强大:
>
> 1. 函数入栈出栈花费时间,不是那么优秀
>
> 2. 宏不会爆栈



### 预定义的宏

| 宏                      | 说明                              |
| ----------------------- | --------------------------------- |
| \_\_DATE\_\_            | 编译日期                          |
| \_\_TIME\_\_            | 编译时间                          |
| \_\_LINE\_\_            | 宏所在行号                        |
| \_\_FILE\_\_            | 文件名                            |
| \_\_func\_\_            | 当前宏所在函数的函数名 （非标准） |
| \_\_FUNC\_\_            | 当前宏所在函数的函数名 （非标准） |
| \_\_PRETTY_FUNCTION\_\_ | 更详细的函数信息（非标准）        |
|                         |                                   |

> 3、4、5 可一起用来打印日志
>
> 非标准：不是所有c语言编译器都支持的宏



### 条件式编译宏

| 函数             | 说明               |
| ---------------- | ------------------ |
| #ifdef DEBUG     | 是否定义了DEBUG宏  |
| #ifndef DEBUG    | 是否没定义DEBUG宏  |
| #if MAX_N == 5   | 宏 MAX_N 是否等于5 |
| #elif MAX_N == 4 |                    |
| #else            |                    |
| #endif           | #if完必须加        |
|                  |                    |



> 1、2为了更好的可移植性
>
> 3、4应用  ： 如手游把MAX_N定义成不同版本，执行不同程序段



### 

###  源代码到可执行

c源码 —^预处理/编译阶段^—> 编译源码 —^编译^—> 对象文件(.o) —^链接^—> 可执行程序



### 🌰1

```c
#include<iostream>
using namespace std;
#define MAX(a, b) ({ \
	__typeof(a) __a = (a); \
	__typeof(b) __b = (b); \
	__a > __b ? __a : __b; \
})

#define P(a) {  \
	printf("%s = %d\n", #a, a); \
}

//#a将a里面的内容以字符串的形式显现出来

//#define MAX(a, b) ((c = (a)), ((c > (b)) ? c : (b)))
//自己打的  问题:不是纯的宏

int main() {
//	int c;
	int a = 7;
	P(MAX(2, 3));
	P(5 + MAX(2, 3));
	P(MAX(2, MAX(3, 4)));
	P(MAX(2, 3 > 4 ? 3 : 4));
	P(MAX(a++, 6));
	P(a);
	return 0;
}
```



> g++  -E  展示编译前的样子,看宏怎么展开



### 🌰2

```c
#include<iostream>
#ifdef DEBUG
using namespace std;
#define log(frm, args...) { \
	printf("[%s : %d] %s ", __func__, __LINE__, #args); \
	printf(frm, ##args);  \
	printf("\n"); \
}
// #将当前变量转换成字符串
// ##连接 将frm和args连成一个东西处理,就能支持参数为0
//下面用abcdef测试一下##
#else
#define log(frm, arg...)    
//没有DEBUG定义为空
#endif

#define contact(a, b) a##b

int main() {
	int a = 3, abc, def;
	int abcdef = 0;
	log("%d", abcdef);
	log("%d", a);
	log("hello world");
	contact(abc, def) = 123;
	log("%d", abcdef);
	return 0;
}

```



> g++ -D DEBUG 定义一个宏



##  内联函数

- 内联函数 让函数尽量像宏


- 不一定内联成功:
  1. 执行过程太复杂
  2. 时间过于复杂
  3. 空间过于复杂





# Seventh

##  0- 字符串

### 写在前面

- 终端上输入的内容，计算机都当作一个字符去处理

- 字符\0底层对应的整数值就是0

  

### 初始化

```c
char str[] = "hello world";
char str[size] = {'h', 'e', 'l', 'l', 'o'};
```



### 相关操作

| 函数                   | 说明                           |      |
| ---------------------- | ------------------------------ | ---- |
| strlen(str)            | 计算字符串长度，以\0作为结束符 |      |
| strcmp(str1, str2)     | 比较                           |      |
| strcpy(dest, src)      | 拷贝, 别用                     |      |
| strncmp(str1, str2, n) | 安全字符串比较                 |      |
| strncpy(str1,str2, n)  | 安全字符串拷贝                 |      |
| memcpy(str1, str2, n)  | 内存拷贝                       |      |
| memcmp(str1, str2, n)  | 内存比较                       |      |
| memset(str1, c, n)     | 内存设置                       |      |
|                        |                                |      |



> - 2、3只能依赖最后一个\0来做结束，很少用，4、5有双保险，一个根据str2的\0，一个根据n,最多比较/拷贝n个字符
>
> - 6、7按字节拷贝，最多拷贝n个字节的内容。它不仅仅可以针对字符串数组，它可以针对别的类型数组，如str1、str2可以是double类型数组的首地址
>
> - 8给该空间每一个字节初始化为c，n代表空间大小。也不一定是字符类型
>
>   memset(arr, 0, sizeof(arr));





| 函数                       | 说明 |      |
| -------------------------- | ---- | ---- |
| scanf(str1, format, ...)   |      |      |
| sprintf(str1, format, ...) |      |      |



##  1- 线性筛



```c
#include<iostream>
using namespace std;
#define max_n 200000

int a[max_n + 5];

int main() {
	for (int i = 2; i <= max_n; i++) {
		if (!a[i]) a[++a[0]] = i;
		for (int j = 1; j <= a[0]; j++) {
			if (i * a[j] > max_n) break;
			a[i * a[j]] = 1;
			if (i % a[j] == 0) break;
		}
	}
	cout << a[10001] << endl;
	return 0;
}
```





# Eighth

##  0- 结构体   

###  基本结构

```c
struct person {
    char name[20];
    int age;
    char gender;
    float height;
}
```



- 开辟的空间大小不是简单累加：

  分析出最大的数据类型，如上面栗子，就以四个字节为一组动态划分空间 



###  内存分配（结构体对齐）

```c
#include<iostream>
using namespace std;

struct node1 {
	char a;
	char b;
	int c;
} n1;

struct node2 {
	char a;
	int c;
	char b;
} n2;

int main() {
	cout << sizeof(n1) << endl;      // 8
	cout << sizeof(n2) << endl;      // 12
	return 0;
}
```

- 尽量把同一类型的字段放一起定义，减少空间浪费



###  改变结构体对齐方式的宏 #pragma pack()

```c
#pragma pack(2)
加上一段代码
sizeof(n1);   // 6
sizeof(n2);   // 8
```



##  1- 共用体（联合体）

###  基本结构

```c
union register {
    struct {
		unsigned char byte1;
    	unsigned char byte2;
        unsigned char byte3;
        unsigned char byte4;
    }  bytes;
    //匿名结构体  不能再初始化变量
    unsigned int number;
};
```

- 共用一段内存单元，以当前类型里最大的字段去开辟空间，如上共用体占4个字节




###  🌰

```c
计蒜客里的共用体ip代码
```



###  🌰  

```c
                      把ip地址转成整形
#include<iostream>
using namespace std;

union IP {
	struct {
		unsigned char a1;
		unsigned char a2;
		unsigned char a3;	
		unsigned char a4;	
	} ip;
	unsigned int num;
};

int main() {
	union IP p;
	char str[100];
	int arr[4];
	while (~scanf("%s", str)) {
		sscanf(str, "%d.%d.%d.%d", arr + 0, arr + 1, arr + 2, arr + 3);
		p.ip.a1 = arr[0];
		p.ip.a2 = arr[1];
		p.ip.a3 = arr[2];
		p.ip.a4 = arr[3];
		printf("%u\n", p.num);
	}
	return 0;
}

输出：
192.168.0.1
-> 16820416
192.168.0.2
-> 33597632

```



> 相差特别多，因为当前机子是小端机，1、2在最低位



###  大端机和小端机

- 大端机：低位放在高地址

- 小端机：低位放在低地址

- 查看是否是小端机

  ```c
  int is_little() {
  	static int num = 1;
  	return ((char *)&num)[0];
  }
  
  // 返回1则是
  ```

  

- 🌰

  ```c
  int num = 0x616263;
  printf("%s\n", (char*)(&num));
  return 0;
  ```

  

###  主机字节序 网络字节序

socket 套接字

将主机字节序转换为网络字节序，因为大端机小端机不一样（查）



#  Ninth

##  0- 变量的地址

###  写在前面

- 底层按字节编址，一个字节有一个地址
- 一个整形有4个地址，第一个地址表示它的地址
- 指针变量也是变量
- int *p, a; *是和p在一起的， 如果是和int在一起的，那a也是指针变量了
- 对64位操作系统而言，需要八个字节表示地址，指针变量的字节数是8字节
- 地址加一是偏移了一个数据类型
- p -> filed 即 (*p).filed 间接引用，要加括号，.的优先级大于\*



###  一个小练习：写出a[1].x的同类写法



```c
struct data {
    int x, y;
};

struct data a[2], *p = a
    
*(a + 1) . x
*(p + 1).x
p[1].x
(&a[1])->x
(&p[1])->x
(a + 1) -> x
(p + 1) -> x
```



###  typedef用法

1. 内建类型重命名

```c
typedef long long ll;
typedef char * pchar;
```

2. 结构体类型重命名

```c
typedef  struct __node{
    int x, y;
}Node, *PNode;
```

3. 函数

```c
typedef int (*func) (int);
```



###  宏和typedef的区别

```c
#define pchar char *
typedef char * ppchar;

int main() {
	pchar p, q;
	ppchar a, b;
	printf("p = %lu, q = %lu\n", sizeof(p), sizeof(q));
	printf("a = %lu, b = %lu\n", sizeof(a), sizeof(b));
	return 0;
}
```



###  main函数参数

```c
int main(int argc, char *argv[], char **env);   
//env环境变量
```

####  🌰

```c
                                            用环境变量判断是否是我访问程序
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

void output(int argc, char *argv[], char *env[]) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	for (int i = 0; env[i]; i++) {
		if (strncmp(env[i], "USER=", 5) == 0) {
			if (strncmp(env[i] + 5, "zyt", sizeof(env[i])) == 0) {
				printf("welcome meinv\n");
			} else {
				printf("get out!!!\n");
				exit(0);
			}
		}
	}
	return ;
}

int main(int argc, char *argv[], char *env[]) {
	output(argc, argv, env);
	return 0;
}

```



###  一份神奇的小代码 ：栈区从高地址开辟

```c
#include<iostream>
using namespace std;

int main() {
	int num = 0x616263;
	int num2 = 0x61626364;
	printf("%s\n", (char*)(&num2));
	return 0;
}

输出dcbacba
```



###  查看abc偏移量

```c
#include<iostream>
#define offset(T, a) ((long)(&(((T *)(NULL))->a)))

using namespace std;

struct data {
	int a;
	double b;
	char c;
};

int main() {
	int num = 0x616263;
	int num2 = 0x61626364;
	printf("%s\n", (char*)(&num2));
	printf("%ld\n", offset(struct data, a));
	printf("%ld\n", offset(struct data, b));
	printf("%ld\n", offset(struct data, c));
	return 0;
}
```





#  Tenth

##  0- 函数的声明与定义

###  声明

```c
void funcA(int);
void funcB(int);
```



###  未定以报错在链接时，未声明报错在编译时

```c
func.cc文件：
#include <stdio.h>

void funcA(int);
void funcB(int);
/*
void funcA(int n) {
	if (n == 0) return ;
	printf("funcA : %d\n", n);
	funcB(n - 1);
	return ;
}

void funcB(int n) {
	if (n == 0) return ;
	printf("funcB : %d\n", n);
	funcA(n - 1);
	return ;
}
*/

test.cpp文件
#include<stdio.h>

void funcA(int);
void funcB(int);

int main() {
	funcA(5);
	return 0;
}

void funcA(int n) {
	if (n == 0) return ;
	printf("funcA : %d\n", n);
	funcB(n - 1);
	return ;
}

void funcB(int n) {
	if (n == 0) return ;
	printf("funcB : %d\n", n);
	funcA(n - 1);
	return ;
}

```



- g++ -c func.cc 通过，g++ -c test.cpp通过，
- g++ test.o 报错，没找到函数定义，g++ test.o func.o 通过
- 如果注释去掉，后者就不对，重复定义



###  头文件和源文件放什么

####  若头文件里放声明加定义

1. #include顺序本不重要，这么做之后，顺序会影响程序编译的正确性

2. 头文件包含多次正常也没影响，而如果定义放进去，这就有影响了
3. 

```c
#ifdefine _HEADER_H
#define _HEADER_H
#endif
```

- 对一个文件编译时，它能保证头文件不被重复包含

4. 对多个文件链接时，就不可



###  <>和""

- g++ -c -I./ header1.cc   -I就能把当前目录添加到系统搜索的目录里去，尖角号括起来的头文件是从系统目录里找的头文件



###  静态链接库：将所有对象文件打成一个包

- 使用者看不见源代码，保留隐私，但是能用



###  动态链接库



###  工程开发标准规范

```bash
mkdir module
mv header* module/
mkdir include
mv header*.h include    #放头文件
mkdir src
mv *.cc src/            #放源代码
mkdir lib
cd src
g++ -c -I../include header1.cc
ar -r libhaizei.a header1.o header2.o header3.o  #创建静态链接库
mv libhaizei.a ../lib/

外部人的代码test.cpp, 只需要把lib和include中的内容
g++ -c -I/module./include test.cpp
g++ -L./module/lib test.o -lhaizei
```


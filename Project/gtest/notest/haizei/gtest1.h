/*************************************************************************
	> File Name: gtest.h
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 19 Jun 2020 09:20:06 PM CST
 ************************************************************************/

#define TEST(a, b) \
void a##_##b(); \
__attribute__((constructor)) \
void add##_##a##_##b() { \
	addfunc(a##_##b, #a " " #b); \
} \
void a##_##b() \


#define EXPECT_EQ(a, b) printf(#a " = " #b " %s\n", \
	(a) == (b) ? "TRUE" : "FALSE");

typedef void (*funcp)();

int RUN_ALL_TESTS();
void addfunc(funcp, const char *);

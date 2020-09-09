/*************************************************************************
	> File Name: test.h
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 14 Jun 2020 02:22:11 PM CST
 ************************************************************************/
#ifndef _TEST_H_
#define _TEST_H_

#define TEST(a, b) \
void a##_haizei_##b(); \
__attribute__((constructor)) \
void add##__haizei__##a##_haizei_##b() { \
	add_function(a##_haizei_##b, #a "_haizei_" #b); \
} \
void a##_haizei_##b()

#define EXPECT_EQ(a, b) printf("%s == %s ? %s\n", #a, #b, (a) == (b) ? "True" : "False")
typedef void (*TestFuncT)();

struct Function {
	TestFuncT func;
	const char *str;
};

int RUN_ALL_TESTS();
void add_function(TestFuncT, const char *);

#endif

/*************************************************************************
    > File Name: ztest.h
    > Author: 
    > Mail: 
    > Created Time: Sun 21 Mar 2021 03:03:13 PM CST
 ************************************************************************/

#ifndef _ZTEST_H
#define _ZTEST_H

#include "linknode.h"

#define TYPE_RET(a) _Generic((a), \
    int : "%d", \
    float : "%f", \
    double : "%lf", \
    long long : "%lld", \
    char* : "%s" \
)

#define P(a, color) { \
	char frm[25]; \
	sprintf(frm, color("%s"), TYPE_RET(a)); \
	printf(frm, a); \
}

#define COLOR(msg, code) "\033[0;1;" #code "m" msg "\033[m"

#define RED(msg) COLOR(msg, 31)
#define GREEN(msg) COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg) COLOR(msg, 34)

#define EXPECT(a, op, b) { \
    __typeof(a) __a = (a); \
    __typeof(b) __b = (b); \
    printf(GREEN("[-----------] ") #a" "#op" "#b " "); \
    if (__a op __b) cnt_suc++, printf(GREEN("TRUE")"\n"); \
    else { \
        printf(RED("FALSE")"\n\n"); \
        printf("\t\t" YELLOW("%s:%d: Faliure")"\n", __FILE__, __LINE__); \
        printf("\t\t\t" YELLOW("expect : " #a " "#op" " #b) "\n"); \
        printf("\t\t\t" YELLOW("actual : ")); \
        P(a, YELLOW); \
		printf(YELLOW(" vs " #b)); \
        printf("\n\n"); \
    } \
    cnt++; \
}

#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)

#define TEST(a, b) \
void a##_##b(); \
__attribute__((constructor)) \
void reg##_##a##_##b() { \
    add_func(a##_##b, #a"_"#b); \
} \
void a##_##b() \

extern int fcnt, cnt, cnt_suc;

struct TestFunc {
    void (*func)();
    const char *fname;
    struct LinkNode p;
};

int RUN_ALL_TESTS();
void add_func(void (*)(), const char *);

#endif

#ifndef __HAIZEI_GTEST_H_
#define __HAIZEI_GTEST_H_

#include<haizei/linklist.h>

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

#define TYPE_STR(a) _Generic((a), \
	int : "%d", \
	double : "%lf", \
	long long : "%lld", \
	float : "%f", \
	char * : "%s" \
)

#define P(a, color) { \
	char frm[1000]; \
	sprintf(frm, color("%s"), TYPE_STR(a)); \
	printf(frm, a); \
}

#define TEST(a, b) \
void a##_##b(); \
__attribute__((constructor)) \
void add##_##a##_##b() { \
	addfunc(a##_##b, #a "_" #b); \
} \
void a##_##b() \


#define EXPECT(a, b, comp) {\
	__typeof(a) _a = (a); \
	__typeof(b) _b = (b); \
	cnt++; \
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
	printf(GREEN("[-----------] ") #a " " #comp " " #b " %s\n", \
	_a comp _b ? GREEN("TRUE") : RED("FALSE")); \
}

#define EXPECT_EQ(a, b) EXPECT(a, b, ==)
#define EXPECT_NE(a, b) EXPECT(a, b, !=)
#define EXPECT_LT(a, b) EXPECT(a, b, <)
#define EXPECT_GT(a, b) EXPECT(a, b, >)
#define EXPECT_LE(a, b) EXPECT(a, b, <=)
#define EXPECT_GE(a, b) EXPECT(a, b, >=)

typedef void (*funcp)();

extern int cnt, cnt_success;

struct Function {
	funcp func;
	const char *name;
	struct LinkNode p;
};

int RUN_ALL_TESTS();
void addfunc(funcp, const char *);

#endif

#ifndef __HAIZEI_GTEST_H_
#define __HAIZEI_GTEST_H_

#include <haizei/linklist.h>

#define EXPECT_EQ(a, b) EXPECT(a, b, ==)
#define EXPECT_NE(a, b) EXPECT(a, b, !=)
#define EXPECT_GT(a, b) EXPECT(a, b, >)
#define EXPECT_LT(a, b) EXPECT(a, b, <)
#define EXPECT_GE(a, b) EXPECT(a, b, >=)
#define EXPECT_LE(a, b) EXPECT(a, b, <=)

#define TYPE_STR(a) _Generic((a), \
	int : "%d", \
	double : "%lf", \
	float : "%f", \
	long long : "%lld", \
	char * : "%s" \
)


#define P(a, color) { \
	char frm[1000]; \
	sprintf(frm, color("%s"), TYPE_STR(a)); \
	printf(frm, a); \
}

#define EXPECT(a, b, comp){ \
	__typeof(a) _a = (a); \
	__typeof(b) _b = (b); \
	cnt++; \
	if (_a comp _b) { \
		printf(GREEN("[-----------]") " %s %s %s " GREEN("True") "\n", #a, #comp, #b);  \
		cnt_success++;                                    \
	} else {                                              \
		printf("\n");                                     \
		printf("\t" YELLOW_HL("%s:%d: Failure") "\n", __FILE__, __LINE__); \
		printf(YELLOW_HL("\t\texpect : " #a " " #comp " " #b "\n\t\t" "actual : "));\
		P(_a, YELLOW_HL); \
		P(" vs ", YELLOW_HL); \
		P(_b, YELLOW_HL); \
		printf("\n\n"); \
		printf(GREEN("[-----------]") " %s %s %s " RED("False") "\n", #a, #comp, #b);  \
	} \
}

#define TEST(testsuit, testcase) \
	void testsuit##_##testcase(); \
	__attribute__((constructor)) \
	void init_##testsuit##_##testcase() { \
		add_func(testsuit##_##testcase, #testsuit "_" #testcase); \
	} \
	void testsuit##_##testcase()

#define COLOR(a, b) "\33[" #b "m" a "\033[0m"
#define COLOR_HL(a, b) "\33[1;" #b "m" a "\033[0m"

#define GREEN(a) COLOR(a, 32)
#define RED(a) COLOR(a, 31)
#define BLUE(a) COLOR(a, 34)
#define YELLOW(a) COLOR(a, 33)

#define GREEN_HL(a) COLOR_HL(a, 32)
#define RED_HL(a) COLOR_HL(a, 31)
#define BLUE_HL(a) COLOR_HL(a, 34)
#define YELLOW_HL(a) COLOR_HL(a, 33)

extern int cnt, cnt_success;

typedef void (*funcp)();

struct Function {
	funcp func;
	const char *name;
	struct LinkNode p;
};

/*自己实现的链表形式
typedef struct node{
	funcp func;
	const char *name;
	struct node *next;
} node;
*/

int RUN_ALL_TESTS();
void add_func(funcp, const char *);

#endif

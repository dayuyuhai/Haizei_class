/*************************************************************************
	> File Name: gtest.h
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 19 Jun 2020 10:57:31 PM CST
 ************************************************************************/

#define TEST(a, b) void a##_##b()

#define EXPECT_EQ(a, b) printf(#a " = " #b " %s", \
	(a) == (b) ? "TRUE" : "FALSE");

int RUN_ALL_TESTS();

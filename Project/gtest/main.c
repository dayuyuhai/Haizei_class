/*************************************************************************
	> File Name: a.c
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 13 Jun 2020 04:37:13 PM CST
 ************************************************************************/

#include<stdio.h>
#include<ztest.h>
#include<linknode.h>

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

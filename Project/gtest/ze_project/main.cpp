/*************************************************************************
	> File Name: a.c
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 13 Jun 2020 04:37:13 PM CST
 ************************************************************************/

#include<stdio.h>
#include<test/test.h>

int add(int a, int b) {
	return a + b;
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

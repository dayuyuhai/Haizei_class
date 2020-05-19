/*************************************************************************
	> File Name: abc.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 19 May 2020 06:39:50 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#pragma pack(2)

struct node1 {
	char a;
	char b;
	int c;
}n1;

struct node2 {
	char a;
	int c;
	char b;
}n2;

int main() {
	cout << sizeof(n1) << endl;
	cout << sizeof(n2) << endl;
	return 0;
}

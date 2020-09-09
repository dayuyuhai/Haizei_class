/*************************************************************************
	> File Name: ip_union.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 19 May 2020 07:15:56 PM CST
 ************************************************************************/

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
		printf("%d\n", p.num);
	}
	return 0;
}

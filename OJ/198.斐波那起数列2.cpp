/*************************************************************************
	> File Name: 198.斐波那起数列2.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 10:16:07 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
    int x;
	cin >> x;
	int n[100005] = {0, 1, 1};
	for (int i = 3; i <= x; i++) {
		n[i] = n[i - 1] + n[i - 2];
		n[i] %= 1000000007;
	}
	cout << n[x] << endl;

	return 0;
}


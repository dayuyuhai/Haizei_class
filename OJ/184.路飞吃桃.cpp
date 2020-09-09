/*************************************************************************
	> File Name: 184.路飞吃桃.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 10:04:38 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int n;

int f(int x){
	if (x == n) return 1;
	return f(x + 1) * 2 + 2;
}
int main() {
	cin >> n;
	cout << f(1) << endl;
	return 0;
}

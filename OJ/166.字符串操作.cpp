/*************************************************************************
	> File Name: 166.字符串操作.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 06:01:30 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;


int main() {
	string a, b;
	int n;
	cin >> a >> n >> b;
	cout << a.length() << endl;;
	cout << a.find('a') << endl;
	a.insert(n - 1, b);
	cout << a << endl;

	return 0;
}


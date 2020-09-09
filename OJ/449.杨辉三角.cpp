/*************************************************************************
	> File Name: 449.杨辉三角.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 10:40:07 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int num[25][25] = {0};
	num[1][1] = 1;
	cout << num[1][1] << endl;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (j != 1) cout << ' ';
			num[i][j] = num[i - 1][j - 1] + num[i - 1][j];
			cout << num[i][j];
		}
		cout << endl;
	}
	return 0;
}



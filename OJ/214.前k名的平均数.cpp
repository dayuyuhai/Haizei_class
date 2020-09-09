/*************************************************************************
	> File Name: 214.前k名的平均数.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 03 May 2020 08:29:10 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

int a[35] = {0};

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n);
	double sum = 0;
	int k;
	cin >> k;
	for (int i = n - 1; i >= n - k; i--) {
		sum += a[i];
	}
	printf("%.2lf\n", sum / k);

	return 0;
}

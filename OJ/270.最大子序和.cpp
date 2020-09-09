/*************************************************************************
	> File Name: 270.最大子序和.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 23 Jun 2020 07:48:07 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max_n 300000

int s[max_n + 5];
int q[max_n + 5], head, tail;

int main() {
	int n, m, ans; 
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];
	head = tail = 0;
	q[tail++] = 0;
	ans = s[1];
	for (int i = 1; i <= n; i++) {
		if (i - q[head] > m) head++;
		ans = max(ans, s[i] - s[q[head]]);
		while (tail - head && s[i] < s[q[tail - 1]]) tail--;
		q[tail++] = i;
	}
	cout << ans << endl;
	return 0;
}


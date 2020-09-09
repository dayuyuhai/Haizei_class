/*************************************************************************
	> File Name: 221。抢气球.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Mon 18 May 2020 08:47:35 AM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

struct k{
	int ind;
	int high;
	int cnt = 0;
}kid[100005];

int ballow[100005];

int cmp1(struct k a, struct k b) {
	return a.high < b.high;
}

int cmp2(struct k a, struct k b) {
	return a.ind < b.ind;
}

int binary_search(int x, int l, int r) {
	if (x < ballow[0]) return 0;
	int head = l, tail = r, mid;
	while (head != tail) {
		mid = (head + tail + 1) >> 1;
		if (ballow[mid] <= x) head = mid;
		else tail = mid - 1;
	}
	return head;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		kid[i].ind = i + 1;
		scanf("%d", &kid[i].high);
	}
	for (int j = 1; j <= m; j++) {
		scanf("%d", &ballow[j]);
	}
	sort(kid, kid + n, cmp1);
	sort(ballow + 1, ballow + m + 1);
	int front = 0, sf;
	for (int i = 0; i < n; i++) {
		sf = front;
		front = binary_search(kid[i].high, front, m);
		kid[i].cnt += front - sf;
	}
	sort(kid, kid + n, cmp2);
	for (int i = 0; i < n; i++) {
		cout << kid[i].cnt << endl;
	}
	return 0;
}

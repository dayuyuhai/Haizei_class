/*************************************************************************
	> File Name: 3.1.ordered_queue.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 23 Jun 2020 06:31:11 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;
int a[10] = {3, 1, 4, 5, 2, 9, 8, 12, 5};

int main() {
	queue<int> q;
	for (int i = 8; i >= 0; i--) {
		if (q.empty() || q.back() > a[i]) q.push(a[i]);
		if (q.size() > 1) q.pop();
		printf("%d ", q.front());
	}
	return 0;
}

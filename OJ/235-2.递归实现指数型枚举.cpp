/*************************************************************************
	> File Name: 235.递归实现指数型枚举.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 11 Aug 2020 06:39:02 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, num[15], num1[15], cnt = 1, mark[15];

void p(int flag) {
    for (int i = 1; i < cnt; i++) {
        (i != 1) && cout << " ";
        (flag == 0) && cout << num[i];
        (flag == 1) && cout << num1[i];
    }
    cout << endl;
}


void func1(int left, int deep) {
    if (left == 0) {
        p(1);
        return ;
    }
    for (int i = 1; i <= n; i++) {
        if (mark[i] == 1) continue;
        mark[i] = 1;
        num1[deep] = i;
        func1(left - 1, deep + 1);
        mark[i] = 0;
    }
}


void func(int start) {
    for (int i = start; i <= n; i++) {
        num[cnt++] = i;
        p(0);
        func1(cnt, 1);
        func(i + 1);
        cnt--;
    }
}

int main() {
    cin >> n;
    func(1);

    return 0;
}

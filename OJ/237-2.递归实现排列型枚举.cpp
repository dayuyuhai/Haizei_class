/*************************************************************************
	> File Name: 235.递归实现指数型枚举.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 11 Aug 2020 06:39:02 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, m, num[15],  mark[15] = {0};

void p() {
    for (int i = 1; i <= m; i++) {
        (i != 1) && cout << " ";
        cout << num[i];
    }
    cout << endl;
}

void func(int left, int deep) {
    if (left == 0) {
        p();
        return ;
    }
    for (int i = 1; i <= n; i++) {
        if (mark[i] == 1) continue;
        mark[i] = 1;
        num[deep] = i;
        func(left - 1, deep + 1);
        mark[i] = 0;
    }
}

int main() {
    cin >> n >> m;
    func(m, 1);

    return 0;
}

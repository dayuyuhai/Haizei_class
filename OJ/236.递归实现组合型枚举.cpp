/*************************************************************************
	> File Name: 235.递归实现指数型枚举.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 11 Aug 2020 06:39:02 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, m, num[15];

void p() {
    for (int i = 1; i <= m; i++) {
        (i != 1) && cout << " ";
        cout << num[i];
    }
    cout << endl;
}

void func(int start, int left, int deep) {
    if (left == 0) {
        p();
        return ;
    }
    for (int i = start; i <= n - left + 1; i++) {
        num[deep] = i;
        func(i + 1, left - 1, deep + 1);
    }
}

int main() {
    cin >> n >> m;
    func(1, m, 1);

    return 0;
}

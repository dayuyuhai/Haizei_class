/*************************************************************************
	> File Name: 235.递归实现指数型枚举.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 11 Aug 2020 06:39:02 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, num[15], cnt = 1;

void p() {
    for (int i = 1; i < cnt; i++) {
        (i != 1) && cout << " ";
        cout << num[i];
    }
    cout << endl;
}

void func(int start) {
    for (int i = start; i <= n; i++) {
        num[cnt++] = i;
        p();
        func(i + 1);
        cnt--;
    }
}

int main() {
    cin >> n;
    func(1);

    return 0;
}

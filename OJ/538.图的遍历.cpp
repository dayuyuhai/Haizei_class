/*************************************************************************
	> File Name: 538.图的遍历.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 15 Oct 2020 06:44:18 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, arr[25][25], check[25], f;

void func(int x) {
    if (check[x] == 1) return ;
    check[x] = 1;
    if (f == 1) cout << '-';
    f = 1;
    cout << x;
    for (int i = 1; i <= n; i++) {
        if (arr[i][x] == 1) func(i);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        func(i);
    }
    cout << endl;
    return 0;
}

/*************************************************************************
	> File Name: 38.兔子繁殖.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Mar 2021 09:55:11 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define MAX_N 100
int f_res[MAX_N + 5];

int f(int n) {
    if (f_res[n]) return f_res[n];
    f_res[n] = f(n - 1) + f(n - 2);
    return f_res[n];
}

int main() {
    int n;
    cin >> n;
    f_res[1] = 1;
    f_res[2] = 2;
    cout << f(n) << endl;
    return 0;
}

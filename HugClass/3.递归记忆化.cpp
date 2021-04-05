/*************************************************************************
	> File Name: 3.递归记忆化.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Mar 2021 09:31:42 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int f_res[1005];

int f(int n) {
    if (f_res[n]) return f_res[n];
    f_res[n] = f(n - 1) + f(n - 2);
    return f_res[n];
}

int main() {
    f_res[1] = 1;
    f_res[2] = 2;
    int n;
    scanf("%d", &n);
    cout << f(n) << endl;
    return 0;
}

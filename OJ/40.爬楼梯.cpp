/*************************************************************************
	> File Name: 40.爬楼梯.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Mar 2021 10:00:07 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define MAX 500
long long f_res[MAX + 5] = {0};

long long f(int n) {
    if (f_res[n] || n == 1) return f_res[n];
    f_res[n] = f(n - 2) + f(n - 3);
    return f_res[n];
}

int main() {
    int n;
    cin >> n;
    f_res[1] = 0;
    f_res[2] = 1;
    f_res[3] = 1;
    cout << f(n) << endl;

    return 0;
}

/*************************************************************************
	> File Name: 3.递推小兔子.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Mar 2021 09:27:03 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int fn_1 = 1;
    int fn_2 = 2;
    for (int i = 3; i <= n; i++) {
        fn_2 = fn_1 + fn_2;
        fn_1 = fn_2 - fn_1;
    }
    cout << fn_2 << endl;
    return 0;
}

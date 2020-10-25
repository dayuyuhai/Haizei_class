/*************************************************************************
	> File Name: 524.体积.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 15 Oct 2020 06:07:15 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, sum, ans, num[25], check[1005];

void func(int s) {
    if (check[sum] == 0) {
        ans++;
        check[sum] = 1;
    }
    for (int i = s; i < n; i++) {
        sum += num[i];
        func(i + 1);
        sum -= num[i];
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    func(0);
    cout << ans - 1 << endl;
    return 0;
}

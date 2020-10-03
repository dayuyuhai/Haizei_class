/*************************************************************************
	> File Name: 392.丢瓶盖.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 22 Sep 2020 08:37:24 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

int n, m, num[100005];

int func2(int dis) {
    int s = 1, last = num[0];
    for (int i = 1; i < n; i++) {
        if (num[i] - last >= dis) {
            s++;
            last = num[i];
        }
    }
    return s;
}

int func() {
    int mid, l = 1, r = num[n - 1] - num[0];
    while (l != r) {
        mid = (l + r + 1) >> 1;
        int s = func2(mid);
        if (s >= m) l = mid;
        else r = mid - 1;
    }
    return l;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    sort(num, num + n);
    cout << func() << endl;
    return 0;
}



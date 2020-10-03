/*************************************************************************
	> File Name: 391.数列分段.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 22 Sep 2020 08:18:28 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

long long n, m, num[100005], tl, tr;

long long func2(long long sum) {
    long long now = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (now + num[i] == sum) {
            cnt++;
            now = 0;
        } else if (now + num[i] > sum) {
            cnt++;
            now = num[i];
        } else {
            now += num[i];
        }
    }
    if (now) {
        cnt ++;
    }
    return cnt;
}

long long func() {
    while (tl != tr) {
        long long mid = (tl + tr) >> 1;
        long long s = func2(mid);
        if (s > m) {
            tl = mid + 1;
        } else {
            tr = mid;
        }
    }
    return tl;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
        tl = max(tl, num[i]);
        tr += num[i];
    }

    cout << func() << endl;

    return 0;
}

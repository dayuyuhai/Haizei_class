/*************************************************************************
	> File Name: 392.丢瓶盖.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 22 Sep 2020 08:37:24 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

int L, n, m, tr = 1000000000, num[50005] = {0};

int func2(int dis) {
    int s = 0, last = num[0];
    for (int i = 1; i <= n + 1; i++) {
        if (num[i] - last < dis) {
            s++;
        } else last = num[i];
    }

    return s;
}

int func() {
    int mid, l = tr, r = L;
    while (l != r) {
        mid = (l + r + 1) >> 1;
        int s = func2(mid);
        if (s <= m) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    cin >> L >> n >> m;
    num[n + 1] = L;
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
        if (num[i] - num[i - 1] < tr) tr = num[i] - num[i - 1];
    }
    tr = tr < L - num[n] ? tr : L - num[n];
    
    cout << func() << endl;
    return 0;
}



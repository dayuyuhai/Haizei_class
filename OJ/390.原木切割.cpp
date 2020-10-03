/*************************************************************************
	> File Name: 390.原木切割.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 22 Sep 2020 07:16:42 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, m, num[100005], tr;

int func2(int len) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += num[i] / len;
    }
    return s;
}

int func() {
    int l = 1, r = tr;
    while (l != r) {
        int mid = (l + r + 1) / 2;
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
        tr = max(tr, num[i]);
    }
    cout << func() << endl;

    return 0;
}

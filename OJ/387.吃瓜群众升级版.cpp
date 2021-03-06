/*************************************************************************
	> File Name: 386.吃瓜群众.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 22 Sep 2020 06:38:06 PM CST
 ************************************************************************/

#include<iostream>
#include <algorithm>
using namespace std;

struct node {
    int num, cnt;
};

bool cmp(node a, node b) {
    return a.num < b.num;
}

node wm[100005];
int n, m;

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> wm[i].num;
        wm[i].cnt = i + 1;
    }
    sort(wm, wm + n, cmp);
    for (int i = 0; i < m; i++) {
        int t, l = 0, r = n - 1;
        cin >> t;
        if (wm[n - 1].num < t) {
            cout << 0 << endl;
            continue;
        }
        while (l != r) {
            int mid = (l + r) / 2;
            if (wm[mid].num < t) l = mid + 1;
            else r = mid;
        }
        cout << wm[l].cnt << endl;
    }

    return 0;
}

/*************************************************************************
	> File Name: 3371.bell.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 29 Oct 2020 06:38:12 PM CST
 ************************************************************************/

#include<iostream>
#include <cstring>
using namespace std;

int n, m, s, edg[500005][3], ans[10005];

int main() {
    memset(ans, 0x3F, sizeof(ans));
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        cin >> edg[i][0] >> edg[i][1] >> edg[i][2];
    }
    ans[s] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[edg[j][1]] = min(ans[edg[j][1]], ans[edg[j][0]] + edg[j][2]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i != 1) cout << " ";
        if (ans[i] == 0x3F3F3F3F) cout << 0x7FFFFFFF;
        else cout << ans[i];
    }
    cout << endl;

    return 0;
}

/*************************************************************************
	> File Name: 590.树獭狂想曲.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 24 Sep 2020 08:37:27 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, m, num[1005][1005], ud[1005][1005], du[1005][1005], sum[1005][1005], ans[1005][3];  // 3 0: max 1 max_cnt 2_second 

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &num[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            ud[i][j] = max(ud[i - 1][j - 1], ud[i - 1][j]) + num[i][j];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            du[i][j] = max(du[i + 1][j + 1], du[i + 1][j]) + num[i][j];
            sum[i][j] = ud[i][j] + du[i][j] - num[i][j];
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (sum[i][j] > ans[i][0]) {
                ans[i][0] = sum[i][j];
                ans[i][1] = j;
            }
        }
        for (int j = 1; j <= i; j++) {
            if (j != ans[i][1] && sum[i][j] > ans[i][2]) {
                ans[i][2] = sum[i][j];
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a == 1 && b == 1) printf("%d\n", -1);
        else {
            if (ans[a][1] == b) printf("%d\n", ans[a][2]);
            else printf("%d\n", ans[a][0]);
        }
    }

    return 0;
}

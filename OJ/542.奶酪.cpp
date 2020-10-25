/*************************************************************************
	> File Name: 542.奶酪.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 20 Oct 2020 06:13:06 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

int t, n, h, r, q[1005][3], start[1005], cnt, endp[1005], check[1005], arr[1005][1005];

int func(int now) {
    if (endp[now] == 1) return 1;
    for (int i = 1; i <= n; i++) {
        if (check[i] == 0 && arr[i][now] == 1) {
            check[i] = 1;
            if (func(i) == 1) return 1;
        }
    }
    return 0;
}

int main() {
    cin >> t;
    while (t--) {
        memset(endp, 0, sizeof(endp));
        memset(check, 0, sizeof(check));
        memset(arr, 0, sizeof(arr));
        cnt = 0;
        cin >> n >> h >> r;
        for (int i = 1; i <= n; i++) {
            cin >> q[i][0] >> q[i][1] >> q[i][2];
            if (q[i][2] <= r) {
                start[cnt++] = i;
            }
            if (q[i][2] + r >= h) {
                endp[i] =1;
            }
            for (int j = 1; j < i; j++) {
                int t0 = q[i][0] - q[j][0], t1 = q[i][1] - q[j][1], t2 = q[i][2] - q[j][2];
                if (sqrt(t0 * t0 + t1 * t1 + t2 * t2) <= 2 * r) {
                    arr[i][j] = arr[j][i] = 1;
                }
            }
        }
        int f = 0;
        for (int i = 0; i < cnt; i++) {
            if (check[start[i]] == 0) {
                check[start[i]] = 1;
                if (func((start[i]))) {
                    cout << "Yes" << endl;
                    f = 1;
                    break;
                }
            }
        }
        if (f == 0) cout << "No" << endl;

    }
    return 0;
}

/*************************************************************************
	> File Name: 2865.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 12 Nov 2020 06:09:43 PM CST
 ************************************************************************/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct node {
    int now, dist;
    bool operator< (const node &b) const {
        return this->dist > b.dist;
    }
};

int n, m, anss = 0x3F, arr[5005][5005], ans1[5005], ans2[5005];

void get_min_route(int *ans, int s) {
    priority_queue<node> que;
    que.push((node){s, 0});
    while (!que.empty()) {
        node temp = que.top();
        que.pop();
        if (ans[temp.now] != 0x3F3F3F3F) {
            continue;
        }
        ans[temp.now] = temp.dist;
        for (int i = 1; i <= n; i++) {
            if (arr[temp.now][i] != 0x3F3F3F3F) {
                que.push((node){i, temp.dist + arr[temp.now][i]});
            }
        }
    }

}

int main() {
    memset(arr, 0x3F, sizeof(arr));
    memset(ans1, 0x3F, sizeof(ans1));
    memset(ans2, 0x3F, sizeof(ans2));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        arr[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        arr[a][b] = min(arr[a][b], c);
        arr[b][a] = min(arr[b][a], c);
    }
    get_min_route(ans1, 1);
    get_min_route(ans2, n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int temp = ans1[i] + ans2[j] + arr[i][j];
            printf("%d 到 %d %d\n", i, j, temp);
            if (temp != ans1[n]) {
                anss = min(temp, anss);
            }
        }
    }
    cout << anss << endl;
    return 0;
}

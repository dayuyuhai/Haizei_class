/*************************************************************************
	> File Name: 3371.dijkstra.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Oct 2020 07:57:23 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

struct node {
    int now, dist;
    bool operator< (const node &b) const {
        return this->dist > b.dist;
    }
};

int n, m, s, arr[1005][1005], ans[1005];

int main() {
    memset(arr, 0x3F, sizeof(arr));
    memset(ans, 0x3F, sizeof(ans));
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        arr[a][b] = min(arr[a][b], c);
    }
    priority_queue<node> que;
    que.push((node){s, 0});
    while (!que.empty()) {
        node temp = que.top();
        que.pop();
        if (ans[temp.now] != 0x3F3F3F3F) continue;
        ans[temp.now] = temp.dist;
        for (int i = 1; i <= n; i++) {
            if (arr[temp.now][i] != 0x3F3F3F3F) {
                que.push((node){i, temp.dist + arr[temp.now][i]});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i != 1) cout << " ";
        if (ans[i] == 0x3F3F3F3F) cout << -1;
        else cout << ans[i];
    }
    cout << endl;
    return 0;
}

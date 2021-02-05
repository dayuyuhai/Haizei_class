/*************************************************************************
	> File Name: 3371.dij.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 29 Oct 2020 06:05:54 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

struct edge {
    int e, dist, next;

};

struct node {
    int now, dist;
    bool operator< (const node &b) const {
        return this->dist > b.dist;
    }
};

edge edg[500005];
int n, m, s, ans[10005], head[10005], mark[10005];

int main() {
    memset(ans, 0x3F, sizeof(ans));
    memset(head, -1, sizeof(head));
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edg[i].e = b;
        edg[i].dist = c;
        edg[i].next = head[a];
        head[a] = i;
    }
    priority_queue<node> que;
    que.push((node){s, 0});
    while (!que.empty()) {
        node temp = que.top();
        que.pop();
        if (ans[temp.now] > temp.dist) {
            ans[temp.now] = temp.dist;
        } else continue;
        for (int i = head[temp.now]; i != -1; i = edg[i].next) {
            int e = edg[i].e, d = edg[i].dist;
            if (ans[e] > ans[temp.now] + d) {
                que.push((node){e, ans[temp.now] + d});
            }
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

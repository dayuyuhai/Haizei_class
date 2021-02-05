/*************************************************************************
	> File Name: tuopu.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Nov 2020 06:15:34 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<stack>
#include<queue>
using namespace std;

struct edge {
    int e, next;
};

edge edg[10005];
int n, m, head[10005], in_degree[10005];

int main() {
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        edg[i].e = b;
        edg[i].next = head[a];
        head[a] = i;
        in_degree[b]++;
    }
    // stack<int> sta;
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) que.push(i);
    }

    while (!que.empty()) {
        int t = que.front();
        que.pop();
        cout << t << "-";
        for (int i = head[t]; i != -1; i = edg[i].next) {
            int e = edg[i].e;
            in_degree[e]--;
            if (in_degree[e] == 0) que.push(e);
        }
    }
    return 0;
}

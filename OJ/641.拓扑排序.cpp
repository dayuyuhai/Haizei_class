/*************************************************************************
	> File Name: 641.拓扑排序.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Nov 2020 06:29:03 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<stack>
#include<queue>
using namespace std;

struct edge {
    int e, next;
};

struct my_int {
    int x;
    bool operator< (const my_int &b) const {
        return this->x > b.x;
    }
};

edge edg[400005];
int n, m, head[2005], in_degree[2005];

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
    priority_queue<my_int> que;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) que.push((my_int){i});
    }
    int flag = 0;

    while (!que.empty()) {
        my_int temp = que.top();
        que.pop();
        if (flag) cout << " ";
        flag = 1;
        cout << temp.x;
        for (int i = head[temp.x]; i != -1; i = edg[i].next) {
            int e = edg[i].e;
            in_degree[e]--;
            if (in_degree[e] == 0) que.push((my_int){e});
        }
    }
    cout << endl;
    return 0;
}



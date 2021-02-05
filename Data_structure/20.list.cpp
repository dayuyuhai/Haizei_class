/*************************************************************************
	> File Name: 20.list.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Oct 2020 08:39:43 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;

struct edge{
    int e, dist, next;
};

edge edg[1005];
int n, m, head[105];

int main() {
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edg[i].e = b;
        edg[i].dist = c;
        edg[i].next = head[a];
        head[a] = i;
    }
    for (int i = 1; i <= n; i++) {
        cout << i << " : ";
        for (int j = head[i]; j != 1; j = edg[j].next) {
            cout << "(" << edg[j].e << "," << edg[j].dist << ")";
        }
        cout << endl;
    }
    return 0;
}

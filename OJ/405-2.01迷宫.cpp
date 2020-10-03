/*************************************************************************
	> File Name: 404-2.01迷宫简易版.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Sep 2020 08:05:43 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

int n, m, check[3005][3005], sx, sy, ans = 1;
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
char mmap[3005][3005];

struct node {
    int x, y;
};

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mmap[i][j];
        }
    }
    queue<node> que;
    cin >> sx >> sy;
    check[sx][sy] = 1;
    que.push((node){sx, sy});

    while (!que.empty()) {
        node temp = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            int x = temp.x + dir[i][0];
            int y = temp.y + dir[i][1];
            if (x < 1 || y < 1 || x > n || y > m) continue;
            if (mmap[x][y] != mmap[temp.x][temp.y] && check[x][y] == 0) {
                ans++;
                check[x][y] = 1;
                que.push((node){x, y});
            }
        }
    }

    cout << ans << endl;

    return 0;
}


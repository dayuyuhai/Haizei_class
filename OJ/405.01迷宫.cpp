/*************************************************************************
	> File Name: 405.01迷宫.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2020 04:41:45 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

char mmap[3005][3005];
int ans[3005][3005];
int m, n, sx, sy, k, temp;

struct node {
    int x, y;
};

queue<node> que;

int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

void func(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (xx < 1 || yy < 1 || xx > n || yy > m) continue;
        if (mmap[xx][yy] != mmap[x][y] && ans[xx][yy] == 0) {
            temp++;
            que.push((node){xx, yy});
            ans[xx][yy] = 1;
            func(xx, yy);
        }
    }
}

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> (&mmap[i][1]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (ans[i][j] == 0) {
                temp = 1;
                que.push((node){i, j});
                ans[i][j] = 1;
                func(i, j);
                while (!que.empty()) {
                    node t = que.front();
                    que.pop();
                    ans[t.x][t.y] = temp;
                }
            }
        }
    }

    while (k--) {
        cin >> sx >> sy;
        cout << ans[sx][sy] << endl;
    }

    return 0;
}




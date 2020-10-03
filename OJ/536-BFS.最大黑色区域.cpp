/*************************************************************************
	> File Name: 535-BFS.瓷砖.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 24 Sep 2020 06:20:36 PM CST
 ************************************************************************/

#include<queue>
#include<iostream>
using namespace std;

int m, n, ans = 0;
char mmap[105][105];

int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

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
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mmap[i][j] == '1') {
                int tmp = 0;
                queue<node> que;
                que.push((node){i, j});
                mmap[i][j] = '0';
                while (!que.empty()) {
                    node temp = que.front();
                    que.pop();
                    for (int i = 0; i < 4; i++) {
                        int x = temp.x + dir[i][0];
                        int y = temp.y + dir[i][1];
                        if (mmap[x][y] == '1') {
                            tmp++;
                            mmap[x][y] = '0';
                            que.push((node{x, y}));

                        }
                    }
                }
                if (tmp > ans) ans = tmp;
            }
        }
    }
    cout << ans + 1 << endl;

    return 0;
}

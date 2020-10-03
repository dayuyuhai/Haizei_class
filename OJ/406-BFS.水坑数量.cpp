/*************************************************************************
	> File Name: 535-BFS.瓷砖.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 24 Sep 2020 06:20:36 PM CST
 ************************************************************************/

#include<queue>
#include<iostream>
using namespace std;

int n, m, ans = 0;
char mmap[2005][2005];

int dir[8][2] = {1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1};

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
            if (mmap[i][j] == '#') {
                ans++;
                queue<node> que;
                que.push((node){i, j});
                mmap[i][j] = '.';
                while (!que.empty()) {
                    node temp = que.front();
                    que.pop();
                    for (int i = 0; i < 8; i++) {
                        int x = temp.x + dir[i][0];
                        int y = temp.y + dir[i][1];
                        if (mmap[x][y] == '#') {
                            mmap[x][y] = '.';
                            que.push((node{x, y}));

                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}

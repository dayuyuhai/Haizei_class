/*************************************************************************
	> File Name: 535-BFS.瓷砖.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 24 Sep 2020 06:20:36 PM CST
 ************************************************************************/

#include<queue>
#include<iostream>
using namespace std;

char mmap[505][505];
int m, n;

int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

struct node {
    int x, y, step;
};

int main() {
    cin >> n >> m;
    queue<node> que;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mmap[i][j];
            if (mmap[i][j] == '2') {
                que.push((node){i, j, 0});
            }
        }
    }
    while (!que.empty()) {
        node temp = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            int x = temp.x + dir[i][0];
            int y = temp.y + dir[i][1];
            if (mmap[x][y] == '.') {
                que.push((node{x, y, temp.step + 1}));
                mmap[x][y] = '#';
            }
            if (mmap[x][y] == '3') {
                cout << temp.step + 1 << endl;
                return 0;
            }
        }
    }
    
    cout << -1 << endl;

    return 0;
}

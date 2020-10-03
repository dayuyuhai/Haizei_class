/*************************************************************************
	> File Name: 304.骑士风度的牛.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Sep 2020 06:19:37 PM CST
 ************************************************************************/

#include<iostream>
#include <queue>
using namespace std;

int n, m;
int dir[8][2] = {1, 2, 1, -2, -1, 2, -1, -2, 2, 1, 2, -1, -2, 1, -2, -1};
char mmap[155][155];

struct node {
    int x, y, step;
};


int main() {
    queue<node> que;
    cin >> m >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mmap[i][j];
            if (mmap[i][j] == 'K') {
                que.push((node){i, j, 0});
            }
        }
    }

    while (!que.empty()) {
        node temp = que.front();
        que.pop();
        for (int i = 0; i < 8; i++) {
            int x = temp.x + dir[i][0];
            int y = temp.y + dir[i][1];
            if (x < 1 || y < 1 || x > n || y > m) continue;
            if (mmap[x][y] == 'H') {
                cout << temp.step + 1 << endl;
                return 0;
            }
            if (mmap[x][y] == '.') {
                mmap[x][y] = '*';
                que.push((node){x, y, temp.step + 1});
            }
        }
    }
    cout << -1 << endl;

    return 0;
}


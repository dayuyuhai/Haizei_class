/*************************************************************************
	> File Name: 396.填涂颜色.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2020 03:39:21 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

int n;
int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
int mmap[35][35];

struct node {
    int x, y;
};


int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mmap[i][j];
        }
    }
    queue<node> que;
    que.push((node){0, 0});
    mmap[0][0] = 2;

    while (!que.empty()) {
        node temp = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            int x = temp.x + dir[i][0];
            int y = temp.y + dir[i][1];
            if (x < 0 || y < 0 || x > n + 1 || y > n + 1) continue;
            if (mmap[x][y] == 0) {
                que.push((node){x, y});
                mmap[x][y] = 2;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j != 1) cout << ' ';
            if (mmap[i][j] == 2) cout << 0;
            else if (mmap[i][j] == 1) cout << 1;
            else cout << 2;
        }
        cout << endl;
    }

    return 0;
}



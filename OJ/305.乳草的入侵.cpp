/*************************************************************************
	> File Name: 305.乳草的入侵.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Sep 2020 06:46:23 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

int m, n, sx, sy, cnt = 0;
char mmap[105][105] = {0};
int dir[8][2] = {0, 1, 1, 0, 0, -1, -1, 0, 1, 1, 1, -1, -1, 1, -1, -1};

struct node {
    int x, y, step;
};

// 判断什么时候搜完
// 1 记录点数 为0搜完
// 2 队列为空

int main() {
    cin >> m >> n >> sy >> sx;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mmap[i][j];
            if (mmap[i][j] == '.') cnt++;
        }
    }
    queue<node> que;
    que.push((node){n - sx + 1, sy, 0});
    mmap[n - sx + 1][sy] = 'M';
    cnt--;
    while (!que.empty()) {
        node temp = que.front();
        que.pop();
        for (int i = 0; i < 8; i++) {
            int x = temp.x + dir[i][0];
            int y = temp.y + dir[i][1];
            if (cnt == 0) {
                cout << temp.step + 1 << endl;
                return 0;
            }
            if (mmap[x][y] == '.') {
                cnt--;
                mmap[x][y] = 'M';
                que.push((node){x, y, temp.step + 1});
            }
        }
    }

    return 0;
}

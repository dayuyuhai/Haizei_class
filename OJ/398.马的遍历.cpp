/***************mZ********************************************************
	> File Name: 396.填涂颜色.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2020 03:39:21 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

int n, m, sx, sy;
int dir[8][2] = {1, 2, 1, -2, -1, 2, -1, -2, 2, 1, 2, -1, -2, 1, -2, -1};
int ans[405][405], check[405][405] = {0};

struct node {
    int x, y, step;
};


int main() {
    cin >> n >> m >> sx >> sy;

    queue<node> que;
    que.push((node){sx, sy, 0});
    check[sx][sy] = 1;

    while (!que.empty()) {
        node temp = que.front();
        que.pop();
        for (int i = 0; i < 8; i++) {
            int x = temp.x + dir[i][0];
            int y = temp.y + dir[i][1];
            if (x <= 0 || y <= 0 || x > n || y > m || check[x][y] == 1) continue;
            ans[x][y] = temp.step + 1;
            check[x][y] = 1;
            que.push((node){x, y, ans[x][y]});
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            (j != 1) && cout << " ";
            if (ans[i][j] == 0) {
                if (check[i][j] == 1) cout << 0;
                else cout << -1;
            } else {
                cout << ans[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}



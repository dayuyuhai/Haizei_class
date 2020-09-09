/*************************************************************************
	> File Name: 404.01迷宫简易版.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2020 04:11:55 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

char mmap[3005][3005];
char check[3005][3005];
int m, n, sx, sy, ans;

int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

void func(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (xx < 1 || yy < 1 || xx > n || yy > m) continue;
        if (mmap[xx][yy] != mmap[x][y] && check[xx][yy] == 0) {
            ans++;
            check[xx][yy] = 1;
            func(xx, yy);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (&mmap[i][1]);
    }
    ans = 1;
    cin >> sx >> sy;
    check[sx][sy] = 1;
    func(sx, sy);
    cout << ans << endl;

    return 0;
}

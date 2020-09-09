/*************************************************************************
	> File Name: 535.瓷砖.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 18 Aug 2020 02:11:46 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

char mmap[100][100];
int m, n, sx, sy, ans;

int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

void func(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (mmap[xx][yy] == '.') {
            ans++;
            mmap[xx][yy] = '#';
            func(xx, yy);
        }
    }
}

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mmap[i][j];
            if (mmap[i][j] == '@') {
                sx = i; 
                sy = j;
            }
        }
    }
    ans = 1;
    func(sx, sy);
    cout << ans << endl;

    return 0;
}

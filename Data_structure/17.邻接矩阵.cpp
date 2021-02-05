/*************************************************************************
	> File Name: 17.邻接矩阵.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Oct 2020 06:10:56 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;

int n, m, arr[105][105];

int main() {
    memset(arr, 0x3F, sizeof(arr));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (arr[a][b] > c) {
            arr[a][b] = c;
            arr[b][a] = c;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr[i][j] == 0x3F3F3F3F) cout << 0 << " ";
            else cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

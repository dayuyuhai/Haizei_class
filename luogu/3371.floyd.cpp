/*************************************************************************
	> File Name: 3371.floyd.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Oct 2020 07:35:42 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;

int n, m, s, arr[1005][1005];

int main() {
    memset(arr, 0x3F, sizeof(arr));
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) {
        arr[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        arr[a][b] = min(arr[a][b], c);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k<= n; k++) {
                arr[j][k] = min(arr[j][k], arr[j][i] + arr[i][k]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        (i != 1) && cout << " ";
        if (arr[s][i] == 0x3F) cout << -1;
        else cout << arr[s][i];
    }

    return 0;
}

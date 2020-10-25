/*************************************************************************
	> File Name: 528.关系网络.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 13 Oct 2020 06:22:10 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

struct node {
    int now, step;
};

int n, x, y, num[105][105], check[105];

int main() {
    cin >> n >> x >> y;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> num[i][j];
        }
    }
    queue<node> que;
    que.push((node){x, 0});
    check[x] = 1;
    while (!que.empty()) {
        node temp = que.front();
        que.pop();
        for (int i = 1; i <= n; i++) {
            if (i == y && num[temp.now][y] == 1) {
                cout << temp.step << endl;
                return 0;
            }
            if (num[temp.now][i] == 1 && check[i] == 0) {
                check[i] = 1;
                que.push((node){i, temp.step + 1});
            }
        }
    }
    cout << 0 << endl;
    return 0;
}

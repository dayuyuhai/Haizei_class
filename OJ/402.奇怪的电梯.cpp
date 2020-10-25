/*************************************************************************
	> File Name: 402.奇怪的电梯.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 13 Oct 2020 06:05:35 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

struct node {
    int now, step;
};

int n, a, b, num[205], check[205];

int main() {
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    queue<node>que;
    check[a] = 1;
    que.push((node){a, 0});


    while (!que.empty()) {
        node temp = que.front();
        que.pop();
        if (temp.now == b) {
            cout << temp.step << endl;
            return 0;
        }
        int up = temp.now + num[temp.now];
        int down = temp.now - num[temp.now];
        if (up <= n && check[up] == 0) {
            check[up] = 1;
            que.push((node){up, temp.step + 1});
        }
        if (down > 0 && check[down] == 0) {
            check[down] = 1;
            que.push((node){down, temp.step + 1});
        }
    }

    cout << -1 << endl;
    return 0;
}

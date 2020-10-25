/*************************************************************************
	> File Name: 537.2.门票问题.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 15 Oct 2020 06:21:17 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

int n, m, fnum, ynum, cnt, ans_cnt;
char num[30], ans[30];

void p() {
    for (int i = 0; i < m; i++) {
        cout << ans[i];
    }
    cout << endl;
    cnt++;
}

void func(int s, int left) {
    if (left == 0) {
        if (fnum >= 2 && ynum >= 1) {
            p();
        }
        return ;
    }
    for (int i = s; i < n; i++) {
        int f = 0;
        if (num[i] == 'a' || num[i] == 'e' || num[i] == 'i' || num[i] == 'o' || num[i] == 'u') {
            f = 1;
            ynum++;
        }
        else fnum++;
        ans[ans_cnt++] = num[i];
        func(i + 1, left - 1);
        if (cnt == 25000) return ;
        ans_cnt--;
        if (f == 1) ynum--;
        else fnum--;
    }
}

int main() {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    sort(num, num + n);
    func(0, m);
    return 0;
}

/*************************************************************************
	> File Name: 390.原木切割.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 22 Sep 2020 07:16:42 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int n, m;
double num[10005], tr;

int func2(double len) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += num[i] / len;
    }
    return s;
}

double func() {
    double l = 0, r = tr;
    while (r - l > 0.00001) {
        double mid = (l + r) / 2;
        int s = func2(mid);
        if (s >= m) l = mid;
        else r = mid;
    }
    return l;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
        tr = max(tr, num[i]);
    }
    double ans = func();
    printf("%.2lf\n", (int)(ans * 100) / 100.0);

    return 0;
}

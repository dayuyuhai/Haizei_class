/*************************************************************************
	> File Name: 4.数字三角形.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Mar 2021 10:03:07 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int a[100][100];
int arr[100][100];

int main() {
    int n, maxx = 0, ansi, ansj;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            arr[i][j] = max(arr[i + 1][j], arr[i + 1][j + 1]) + a[i][j];
            if (maxx < arr[i][j]) {
                maxx = arr[i][j];
                ansi = i, ansj = j; 
            }
        }
        cout << a[ansi][ansj] << " ";
    }
    cout << endl;
    cout << arr[1][1] << endl;
    return 0;
}

/*************************************************************************
	> File Name: 46.切割回文.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 18 Mar 2021 09:01:28 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int dp[500005];

int main() {
    string s;
    cin >> s;
    dp[0] = 1;
    int j;

    for (int i = 1; s[i]; i++) {
        if (s[i - 1] == s[i]) {
            dp[i] = dp[i - 1];
            cout << dp[i] << endl;
            continue;
        }
        for (j = i - 1; j >= 0; j--) {
            if (dp[j] == dp[i - 1] - 1) break;
        }
        if (s[j] == s[i]) dp[i] = dp[i - 1] - 1;
        else dp[i] = dp[i - 1] + 1;
        cout << dp[i] << endl;
    }
    cout << dp[s.length() - 1] - 1 << endl;
    return 0;
}

/*************************************************************************
	> File Name: 169.密码翻译.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 09:30:57 PM CST
 ************************************************************************/

#include<iostream>
#include<map>
using namespace std;

int main() {
	int n, t;
	char c;
	cin >> n;
	map <char, int> m;
	while (n--) {
		cin >> c >> t;
		m.insert(pair<char, int>(c, t));
	}
	string s;
	cin >> s;
	int sum = 0;
	for (int i = 0; i < s.length(); i++) {
		if (m.find(s[i]) != m.end()) {
			sum += m[s[i]];
		}
	}

	cout << sum << endl;

	return 0;
}

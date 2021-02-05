/*************************************************************************
	> File Name: 2.字符串.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Jan 2021 04:52:53 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<string>

using namespace std;

int main() {
/*
    string s = "abcdefg";
    string d(begin(s) + 2, begin(s) + 5);

    cout << d << endl;
*/
/*
    char a[10] = "abcdefg";
    memmove(a + 6, a + 5, strlen(a + 5) + 1);
    strncpy(a + 2, "XYZW", 4);

    char b[10] = "abcdefg";
    strncpy(b + 2, "UV", 2);
    memmove(b + 4, b + 5, strlen(b + 5) + 1);

    cout << a << " " << b << endl;
*/
/*
    string a = "abcdefg";
    a.replace(begin(a) + 2, begin(a) + 5, "XYZW");

    string b = "abcdefg";
    b.replace(begin(b) + 2, begin(b) + 5, "UV");

    cout << a << " " << b << endl;
*/
/*
    char s[] = "abcdefg";
    char *x = strstr(s, "cde"); // x == s + 2
    char *y = strstr(s, "CDE"); // y == nullptr
*/
    string s = "abcdefg";
    auto x = s.find("cde");     // x == 2
    auto y = s.find("CDE");     // y == string::npos

    cout << x << " " << y << endl;
    return 0;
}

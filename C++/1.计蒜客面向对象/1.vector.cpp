/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Jan 2021 03:35:57 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
    /*
    vector<int> a(10);
    vector<int> b(10, 0);
    vector<int> c = {1, 2, 3, 4, 5};

    vector<int> a = {1, 2, 3, 4, 5};
    int sum = 0;
    for (auto x : a) {
        sum += x;
    }
    */

    /*
    int a[10] = {1, 23, 4, 5};
    int b[10] = {4, 3, 2, 4};
    vector<int> a = {1, 32, 23, 4};
    vector<int> b = {3, 2, 5, 4};
    auto it = find_first_of(begin(a), end(a), begin(b), end(b));
    bool found = (it != end(a));
    cout << found << endl;

    for (int i = 0; i < 10; i++) {
        cout << &a[i] << endl;
    }
    
    cout << it << endl;
    cout << end(a) << " " << begin(a) << endl;
    */

    vector<int> a = {3, 2, 3, 43};
    sort(begin(a), end(a), [](int x, int y){return x >= y; });
    for (auto x : a) {
        cout << x << endl;
    }

    return 0;
}

/*************************************************************************
	> File Name: 21-random_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Dec 2020 10:51:58 AM CST
 ************************************************************************/

#include<iostream>
#include<ctime>
using namespace std;

int main() {
    srand(time(0));
    int op, val;
    #define MAX_OP 20
    for (int i = 0; i < MAX_OP; i++) {
        switch (rand() % 5) {
            case 0 :
            case 1 : printf("0 %d\n", rand() % 15);
            case 2:
            case 3:
            case 4:
        } 
    }
    return 0;
}
